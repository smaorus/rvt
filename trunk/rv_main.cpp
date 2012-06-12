/* The main file of the Regression Verification tool */

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <assert.h>

#include <rv_error.h>
#include <rv_consts.h>
#include <rv_macros.h>
#include <rv_parse.h>
#include <rv_collect.h>
#include <rv_replace.h>
#include <rv_funcpair.h>
#include <rv_loops.h>
#include <rv_indfunc.h>
#include <rv_treecomp.h>
#include <rv_funcdfs.h>
#include <rv_propagate.h>
#include <rv_decompose.h>
#include <rv_temps.h>
#include <rv_gen.h>
#include <rv_commands.h>
#include <rv_options.h>
#include <rv_traversal.h>
#include <rv_array_assume.h>
#include "rv_glob.h"
#include "rv_dataflow.h"

#define RV_SECTION RV_SEC_MAIN

using namespace std;

unsigned rv_debug_flags = 0;

RVParse* prvhooks = NULL;


///<summary>Removes assert(...) statements from the source code </summary>
class RVDeassertifier : public RVWalk {
public:
	void deassertify(Project *pt) {
		RVBoolStatus ret(true);
		Statement* first_st = get_glob_stemnt(pt);

		for(Statement* st = first_st; st; st = st->next)
			ret.assign( RVWalk::process(st) && ret , __FUNCTION__, DBG);
	}

	virtual bool process(Symbol* s0p) { return true; }

	virtual bool try_replace(Statement** s0p) {
    	if ((*s0p)->type != ST_ExpressionStemnt)
    		return true;
    	Expression *expr = static_cast<ExpressionStemnt*>(*s0p)->expression;
    	if (expr->etype != ET_FunctionCall)
    		return true;

    	FunctionCall *call = static_cast<FunctionCall*>(expr);
    	if (call->function->etype != ET_Variable)
    		return true;

    	if (((Variable *)call->function)->name->name == "assert")
    		*s0p = new Statement(ST_NullStemnt, call->location);

    	return true;
    }
};


const string RVMain::UNINITED("UNINITED");

RVMain::RVMain(void) {
	init();
}

void RVMain::init()
{
   base_dir = ".";
   semchk_dir = UNINITED;
   base_name = "";
   direct_fname = UNINITED;
   side0_fpath = UNINITED;
   side1_fpath = UNINITED;
   fuf_fname = "";
   m_fufSet = UNSET;
   rel_fname = "";
   main_name = "main";

   decision_params.allow_different_callees = true; /* = allow semchk even if callee(s) equality is unknown */
   decision_params.extern_funcs_are_ufs = true;    /* assume external functions (without body) are UFs if they have the same prototype */
   decision_params.allow_cps_in_ufs = false; /* convert funcs to UFs even if they or their subtrees
						   contain check-points (CPs). These CPs are checked by 
						   access check during semchks*/
   decision_params.allow_ubs = true;        /* allow UnBounded Structures in UFs */

   // detach_typedef = ""; // ofer: removed

   delta_dk = 1;   
   omega_total_bound = 0;
   semchk_timeout = 0;     
   
   use_sem = true;    /* = use semantic check (run decision procedure) to detect UFs */
   dk = 2;            /* The maximum value of ubs_depth_k during the excecution */
   ufs_look_back = 1; /* how many calls back on the other side the UF searches to find simmilar inputs to generate the same output. */
   max_records = 5;  /* max records in chanels and UF arrays */
   K = 0;             /* equivalence check bound (0 means infinite) */

   ubs_depth_k = 1;   /* how deep we unwind UBS arguments and return value. */ 

   keep_all_code = false;     /* keep unneeded funcs */
   semchk_recursive = true;   /* semchk recursive function by replacing therecursive call by a call to its UF version.  */
   arrays_to_uas = false;
   test_ctool = false;     /* Only parse side 0 and print it (debug only). */  
   refined = false; // ofer
   completeness = 0; // ofer
   run_cil = false; // ofer: whether to call cil as preprocessing
   mutual_term_check = false; //whether the current run checks mutual termination
   external_inputs = 0;

   // The following dynamically allocated objects are released in ~RVOption():
   m_pLog = new ofstream("rv_log");
   m_pDirectives = new RVDirectives;
   m_bAbortIfUnknownCbmcErr = true;
   m_c99 = false;
}


bool RVMain::do_test_ctool(std::string& fname)
{
  RVParse parser;
  Project* pt = NULL;
  string filePath = fullPath(fname);
  std::ifstream file( filePath.data() );
  if( !file.is_open() ) {
	rv_errstrm << "Error: Unable to open C source file: \"" << filePath << "\"\n";
	return false;
  }

  prvhooks = &parser;
  
  bool ret = prvhooks->do_parse(&file, fname);

  if( ret ) {
	pt = parser.take_parsetree();
	rv_errstrm << **(pt->units.end() -1) <<"\n";
  }

  file.close();
  delete pt;

  return ret;
}
  



RVBoolStatus RVMain::parse_side(const RVSide& side, std::string& side_fpath)
{
  rv_parser.set_side(side);

  RVGlob::counters(RVGlob::GLBL_EXTERNAL_INPUTS, 0);
  bool ret = rv_parser.parse_path(side_fpath, side.toString("side"));

  if (side == SIDE1 && external_inputs != RVGlob::counters(RVGlob::GLBL_EXTERNAL_INPUTS))
	  endl(rv_errstrm << "Warning: different number of external inputs");
  external_inputs = std::max(external_inputs, RVGlob::counters(RVGlob::GLBL_EXTERNAL_INPUTS));
 
  return RVBoolStatus(ret, __FUNCTION__, DBG);
}


RVBoolStatus RVMain::process_directives(void) {
  return RVBoolStatus(accessDirectives().parse_path(fullPath(direct_fname), "directives"),
		              __FUNCTION__, DBG);
}


RVBoolStatus RVMain::relate_globals_from_rel_file(void) {
  bool ret = true;
  SymEntry*  item;
  RVFuncPair*  pfp;
  SymEntry* se0;
  SymEntry* se1;

  ScopeTbl* fs0 = rv_parser.get_file_scope(0);
  ScopeTbl* fs1 = rv_parser.get_file_scope(1);

  RVTreeComp comp;
  bool s0_ok, s1_ok;
  
  HashTblIter it = rv_ufs.get_func_pair_iter(0);  
  FORIT(item,it) {
	pfp = (RVFuncPair*)item->u2FunctionDef;
	if( !pfp || pfp->origin != RVFuncPair::REL )
	  continue;

	s0_ok = s1_ok = true;
  
	se0 = fs0->Lookup( pfp->side_name[0] );
	se1 = fs1->Lookup( pfp->side_name[1] );

	s0_ok = RVCtool::is_global_var(se0);
	s1_ok = RVCtool::is_global_var(se1);
  
	if( !s0_ok && !s1_ok ) // probably a func
	  continue;

	if( s0_ok != s1_ok ) { // only one is global var
	  rv_errstrm << "Error: relate_globals_from_rel_file(): symbol "
	"\"" << (s0_ok? se1->name: se0->name) <<"\" on side "<<(s0_ok?1:0)<<
	"(although its counterpart on the other side is).";
	  rv_ufs.del_pair(pfp);
	  ret = false;
	  continue;
	}
	
	if( !comp.eq_type(se0->uVarDecl->form, se1->uVarDecl->form) ) {
	  rv_errstrm << "The next global variables: \""<< se0->name <<"\" and "<< se1->name <<
	",\n  which are related by rel_file \""<< rel_fname <<
	"\" has different definitions on different sides.";
	  rv_ufs.del_pair(pfp);
	  ret = false;      
	  continue;
	}

	// remove previous relating connections:
	if( se0->equalTo && se0->equalTo->equalTo )
	  se0->equalTo->equalTo = NULL;
	if( se1->equalTo && se1->equalTo->equalTo )
	  se1->equalTo->equalTo = NULL;
	
	se0->equalTo = se1;
	se1->equalTo = se0;

  } /* FORIT */

  return RVBoolStatus(ret, __FUNCTION__, DBG);
}
	

void RVMain::relate_globals_of_same_name()
{
  SymEntry* se0;
  SymEntry* se1;

  ScopeTbl* fs0 = rv_parser.get_file_scope(0);
  ScopeTbl* fs1 = rv_parser.get_file_scope(1);

  RVTreeComp comp;

  /*===== We assume globals of same name and type on both sides are equivalent =====*/

  HashTblIter hit(fs0->htab);
  for(se0 = hit.begin(); !hit.end(); se0 = hit.next())
	if( RVCtool::is_global_decl(se0) ) {

	  /* find the same name and type global on other side: */
	  se1 = fs1->Lookup( se0->name );
	  if( se1 && RVCtool::is_global_var( se1 ) &&
	  comp.eq_type(se0->uVarDecl->form, se1->uVarDecl->form) ) {       

	if( !se0->equalTo && !se1->equalTo ) {
	  se0->equalTo = se1;
	  se1->equalTo = se0;
	} else {	
	  if( se0->equalTo != se1 || se1->equalTo != se0 )
		rv_errstrm << "Warning: relate_globals_of_same_name(): \"" << se0->name <<
		  "\" (on side 0 or 1)\n  was already related before - but not to each other.\n";
	}
	  }
	} /* if() */
}


void RVMain::sort_global_vectors(int side)
{
  SymEntry* se;
  ScopeTbl* fs = rv_parser.get_file_scope(side);
  RVFuncNode* fnode;

if(DBG) rv_errstrm << "\n\nStart sort_global_vectors(), side "<< side << DBG_INFO << " \n"; 

  HashTblIter hit(fs->htab);
  for(se = hit.begin(); !hit.end(); se = hit.next())
	if( RVCtool::valid_function(se) ) {
	  fnode = &se->u2FunctionDef->fnode;
	  fnode->read.unique_sort();
	  fnode->written.unique_sort();

if(rv_debug_flags & RV_DBG_CALLGRAPH) {
  rv_errstrm << "Function " <<  DBG_INFO << se->name << ":\n";
  se->u2FunctionDef->fnode.read.print("directly read globals: " , rv_errstrm);
  se->u2FunctionDef->fnode.written.print("directly written globals: ", rv_errstrm);
}
 
	}

if(DBG) rv_errstrm << "End sort_global_vectors()\n"; 
}


RVBoolStatus RVMain::create_call_graph(int side, bool collect_arrays /*=false*/)
/* also collects read/write info of globals used in each function */
{
	bool ret = true;
	RVCollect wcol(is_checking_partial_equiv());
	SymbolVector all_read_globs, all_written_globs;

	if (DBG) rv_errstrm << "\n\nStart creating call graph of side " << side << DBG_INFO << " \n";

	FunctionDef* func = NULL;
	SymEntry* se = NULL;
	ScopeTbl* fs = rv_parser.get_file_scope(side);
	HashTblIter hit(fs->htab);

	RVCollectArrayRefs array_ref_collector;
	if( collect_arrays )
		wcol.set_array_ref_collector(&array_ref_collector);

	/* should be in order of func declaration: */
	Statement* st = RVCtool::get_glob_stemnt(rv_parser.get_parsetree(side));
	for(; st; st = st->next, func = NULL ) {

		if( st->isFuncDef() ) {
			func = (FunctionDef*)st;
			if( !wcol.collect(func, rv_parser.get_parsetree(side), &accessDirectives(), side) ) {
				rv_errstrm << "Warning: Failed to collect ArgTypes in function: "<<
						*func->FunctionName() <<" \n";
				ret = false;
			}
		}
		else if( st->isDeclaration() && (func = RVCtool::try_get_function(st)) ) {
			if( func->fnode.has_body() ) /* init argtype number on prototype - before use */
				ret = wcol.init_argtypes( func ) && ret;
			else
				ret = wcol.collect(func, rv_parser.get_parsetree(side), &accessDirectives(), side) && ret;
		}

		/* collect func_flags from .rv file */
		if( func )
			func->fnode.func_flags |= accessDirectives().get_func_flags(side, func->FunctionName()->name);
	} /* for(st...) */

	/* collect the maximum omega bound: */
	if( omega_total_bound < wcol.get_omega_deref_bound() )
		omega_total_bound = wcol.get_omega_deref_bound();

	for(se = hit.begin(); !hit.end(); se = hit.next())
		if( RVCtool::valid_function(se) ) {
			se->u2FunctionDef->fnode.sort_vectors();
			all_read_globs.add_dup(se->u2FunctionDef->fnode.read);
			all_written_globs.add_dup(se->u2FunctionDef->fnode.written);
		}

	if(rv_debug_flags & RV_DBG_CALLGRAPH) {
		for(se = hit.begin(); !hit.end(); se = hit.next())
			if( RVCtool::valid_function(se) ) {
				rv_errstrm << "Function " << DBG_INFO << se->name << ":\n";
				se->u2FunctionDef->fnode.print_vectors( rv_errstrm, true );
			}
	}

	/* collect read only globals for this side: */
	all_read_globs.unique_sort();
	all_written_globs.unique_sort();
	all_read_globs.filter_common(all_written_globs);
	read_only_globals[side] = all_read_globs;
	all_written_globs.delete_all(); // we don't need these.

	if(side == 1)
		if (DBG) {
			rv_errstrm << "omega_total_bound = "<< omega_total_bound << " \n";
			rv_errstrm << "end creating call graph of side " << side << " \n\n";
		}

	return RVBoolStatus(ret, __FUNCTION__, DBG);
}


void RVMain::filter_common_read_only_globals()
  // keep only those related globals which are read only on both sides
{
  SymbolVector filtered[2];
  Symbol* related;
  
  SymbolVector::const_iterator it;
  FORVEC(it, read_only_globals[0]) {
	related = read_only_globals[1].find_related(*it);
	if( related ) {
	  // Note: related vars has also the same initializers.

	  filtered[0].push_back((*it)->dup());
	  filtered[1].push_back(related->dup());
	}
  }

  read_only_globals[0].delete_all();
  read_only_globals[0] = filtered[0];

  filtered[1].unique_sort(); // we may have spoiled the order
  read_only_globals[1].delete_all();
  read_only_globals[1] = filtered[1];
}


RVBoolStatus RVMain::convert_loops_to_rec(void) {
  bool ret = true;
  ScopeTbl* file_scope = NULL;  /* the scope to which to add the new function.*/
  FunctionDef* func = NULL;
  Symbol* sym;

  std::string side0_rec_fname = side0_fpath + RV_LOOPS_TO_REC_EXT; 
  std::string side1_rec_fname = side1_fpath + RV_LOOPS_TO_REC_EXT; 
  
  for(int side = 0; side < 2; side++)
  {
	file_scope = rv_parser.get_file_scope(side);

	rv_loops.set_side(side);
	RVDischarger discharger;
	RVTemp temps;
	temps.open(discharger, side? side1_rec_fname : side0_rec_fname);
	temps.print("\n\n");
	
	Project* pt = rv_parser.get_parsetree(side);

	/*if( detach_typedef != "" ) { // ofer: removed. Activated by a flag; not clear what it does.
	  rv_detach_pointer_value.add_pointer_type(detach_typedef, side);
	  ret = rv_detach_pointer_value.process_all(pt, side) && ret;
	}
  */
    /* fix ellipsis funcs and indirect calls: */
	ret = rv_indirect_funcs.process_all(pt, side) && ret;
	ret = rv_indirect_funcs.gen_all_func_ind_enums(temps, pt, side) && ret;

	/* safety check: */
	if( !RVCtool::get_glob_stemnt(pt) )
	  return RVBoolStatus(false, __FUNCTION__, DBG);

	Statement** pst = &(pt->Parse_TOS->transUnit->head);
	Statement*  st = NULL;

	/* generate all globals except funcs: */
	for(; *pst; pst = &((*pst)->next) )
	{
	  st = *pst;

	  /* for functions - print only prototypes */
	  if( st->isFuncDef() ) {
		  func = static_cast<FunctionDef*>(st);
		  sym = func->FunctionName();
		  if( !sym || !func->decl ) {
			  rv_errstrm << "Error: NULL function symbol or declaration. at: ";
			  st->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
			  ret = false;
		  }
		  func->decl->print(temps.get_strm(), true, 0);
		  temps.print(";\n");
	  }
	  else st->print(temps.get_strm(), 0);  // just print

	  temps.print("\n");
	}
	
	/* for each Function: */
	RVReplaceLoopCalls rv_replace_loop_calls;
	st = RVCtool::get_glob_stemnt(pt);
	for(; st; st = st->next )
	  if( st->isFuncDef() ) {
		  func = static_cast<FunctionDef*>(st);
		  rv_loops.print_protos(temps, func, file_scope);
		  rv_replace_loop_calls.replace(func, pt);  // Ofer: stores func's loops in RVLoop, creates the call to them in func. Uses go().. etc hence hard to follow. 
		  func->print(temps.get_strm(),0);
		  temps.print("\n");
		  rv_loops.gen_loop_funcs(temps, func); // Ofer: creates the new recursive functions
		  temps.print("\n");
	  }

	/*if( detach_typedef != "" ) // ofer: removed
	  ret = rv_detach_pointer_value.gen_all_fix_funcs(rv_temps) && ret;*/

	/* generate all indirect func hubs: */
	ret = rv_indirect_funcs.gen_all_class_hubs(temps, pt, side, true) && ret;

	temps.close(discharger);
  } /* for( side ) */

  rv_loops.clear();
  
  side0_fpath = side0_rec_fname;
  side1_fpath = side1_rec_fname;

  if( !ret )
	rv_errstrm << "Error: Failed to convert loops to recursion or "
	  "fix problematic source code constructs.\n";

  return RVBoolStatus(ret, __FUNCTION__, DBG);
}


string RVMain::fullPath(const std::string& fname, const char *ext) const {
	return rv_commands.combineFilePath(base_dir, fname, ext);
}


/* this function is currently not in use */
RVBoolStatus RVMain::abandone_output(int f0_id) { // ofer
	// output = offending output from counterexample. Need a special case for retval because it is not carried by united_argtypes;
	unsigned char output = 0; 

	RVFuncPair* pfp = rv_ufs.getFuncPairById(f0_id, 0, true);
	return RVBoolStatus(pfp->abandone_output(output), __FUNCTION__, DBG);
}


bool RVMain::find_arrays() { // YL
	Project* pt;
	pt = rv_parser.get_parsetree(0);
	RVGlob::getArrHooks().find_arrays(pt->units[0],0);
	pt = rv_parser.get_parsetree(1); 
	RVGlob::getArrHooks().find_arrays(pt->units[0],1);
	return RVGlob::getArrHooks().array_vec0.size() > 0;
}

void RVMain::prepareFuncCallCountAnalyses(const RVGlobLists& parser,
		                                  const vector<string>& mapf0,
		                                  const vector<string>& mapf1)
{
	prepareFuncCallCountForSide(parser, SIDE0, mapf0);
	prepareFuncCallCountForSide(parser, SIDE1, mapf1);
}

void RVMain::prepareFuncCallCountForSide(const RVGlobLists& parser,
									     const RVSide& side,
				                         const vector<string>& mapfside)
{
	int idx = side.index();
	Utils::expandPtrVec(m_callChainCounter, idx+1);
	assert(m_callChainCounter[idx] == NULL);
	Project *pt = parser.get_parsetree(side);
	Statement* st = RVCtool::get_glob_stemnt(pt);
	if (st == NULL)	return;
	m_callChainCounter[idx] = new RVFuncCallCountAnalysis(st, 1);
	vector<string>::const_iterator it;
	for (it = mapfside.begin(); it != mapfside.end(); ++it)
		m_callChainCounter[idx]->addCallee(*it);	
}

///<summary>
///Counts how many <paramref name="callee" /> is called when execution
///starts from *<paramref name="pFromFunc" />. Recursive and non-recursive
///calls are counted separately. The maximum between the counts is returned
///<summary>
///<param name="side"> the side </param>
///<param name="pFromFunc">
///the execution start function;
///if NULL, RVMain::main_name is the starting function
///</param>
///<param name="callee">
///the name of the function whose calls are counted
///</param>
unsigned RVMain::countMaxCallChain(const RVSide& side,
		                           const std::string* pFromFunc,
		                           const string& callee) {
	const string& from = pFromFunc? *pFromFunc : main_name;
	unsigned res = countMaxCallChainFromTo(side, from, callee);
	if ( from != callee )
		res = max(countMaxCallChainFromTo(side, callee, callee), res);
	return res;
}

unsigned RVMain::countMaxCallChainFromTo(const RVSide& side,
			                             const std::string& from,
			                             const std::string& callee) {
	Project *pt = rv_parser.get_parsetree(side);
	SymEntry *fromEntry = RVCtool::lookup_function(from, pt);
	return m_callChainCounter[side.index()]->countCalls(fromEntry, callee);
}

///<summary>
/// runs three preprocessing steps: cpp, cil and outline
///</summary>
void RVMain::preprocess(string& S0, string& S1) {
  rv_commands.cpp(side0_fpath, S0);
  rv_commands.cpp(side1_fpath, S1);     

  if (run_cil) {
	  string out0 = "S0.cil.c", out1 = "S1.cil.c";

	  rv_commands.cil(S0, out0);
	  rv_commands.cil(S1, out1);
	  S0 = out0;
	  S1 = out1;
  }
  
  if (RVGlob::flags(RVGlob::GLBL_OUTLINE)) {  // adding headers for rv_mult, rv_div, rv_mod. headers are needed for the type propagation later.
	  rv_commands.outline_header("rv_outline.h", S0); // replace with macro!!
	  rv_commands.outline_header("rv_outline.h", S1);
  }
}



RVIntStatus RVMain::main(void) {
  side0_fpath = fullPath(side0_fpath);
  side1_fpath = fullPath(side1_fpath);

  // DEBUG 
  rv_commands.check_syntax(side0_fpath, side1_fpath, m_c99); // check syntax of input files with gcc.
  if( test_ctool )	return RVIntStatus(do_test_ctool(side0_fpath)? 0 : 1, __FUNCTION__, DBG);

  if(DBG) rv_errstrm << DBG_INFO << "P1 - after syntax test + testing CTOOL\n"; 

  if (direct_fname != "UNINITED") {
	  if( !process_directives() ) fatal_error("problem in processing directives file\n");
	  if(DBG) rv_errstrm << DBG_INFO << "P2 - after Process Directives\n";
  }
    
  string S0 = fullPath("S0.c"), S1 = fullPath("S1.c");
  preprocess(S0, S1);
  
  if( !parse_side(SIDE0, S0) || !parse_side(SIDE1, S1) )
	return RVIntStatus(1, DBG_INFO, DBG);

  if(DBG) rv_errstrm << DBG_INFO << "P2.5 - after parsing the sides\n";

  RVTypeProp rv_type_prop;
  if( !rv_type_prop.process_all(rv_parser.get_parsetree(SIDE0),SIDE0) ||
	  !rv_type_prop.process_all(rv_parser.get_parsetree(SIDE1),SIDE1) )
	return RVIntStatus(1, DBG_INFO, DBG);

  if(DBG) rv_errstrm << DBG_INFO << "P3 - after type propagation\n";

  RvTraversal pt1(rv_errstrm, false);   
  RVGlob::pushPtr(RVGlob::GLOB_ARRHOOKS, &pt1);

  if (find_arrays()) {
	 pt1.prt_array_vec(0,1);
	 pt1.prt_array_vec(1,1);
  }

  RVDeassertifier deassertifier;
  deassertifier.deassertify(rv_parser.get_parsetree(SIDE0));
  deassertifier.deassertify(rv_parser.get_parsetree(SIDE1));

  if( !create_call_graph(0) || !create_call_graph(1) )
	return RVIntStatus(1, DBG_INFO, DBG);

  RVDequalifier dequalifier;
  dequalifier.dequalify(rv_parser.get_parsetree(SIDE0),SIDE0);
  dequalifier.dequalify(rv_parser.get_parsetree(SIDE1),SIDE1);

  if(DBG) rv_errstrm << DBG_INFO << "P3.5 - after creation of first call graph\n";

  RVArgTypesDfs  arg_types_dfs1;
  arg_types_dfs1.propagate_argtypes(rv_parser.side_parsetree, main_name);

  /* we may have added read/write globals to funcnodes: */
  sort_global_vectors(0);
  sort_global_vectors(1);

  if(DBG) rv_errstrm << DBG_INFO << "P4 - after propogating argtypes, and sorting the vectors\n";

  // loop to recursion
	
  if(DBG) rv_errstrm << DBG_INFO << "before convert_loops\n";

	if( !convert_loops_to_rec() )
	  return RVIntStatus(1, DBG_INFO, DBG);

	pt1.clear_arrays(0);
	pt1.clear_arrays(1);

	if(DBG) rv_errstrm << DBG_INFO << "after convert_loops - reparse\n";	

	if (RVGlob::flags(RVGlob::GLBL_OUTLINE)) {  // adding rv_mult, rv_div, rv_mod. Need actual functions because of 1) possible use of -refine, and 2) some of these functions can be used only on one side.
		rv_parser.add_outline_bodies(side0_fpath, side1_fpath, refined);
		RVGlob::flags(RVGlob::GLBL_OUTLINE_NOW, 0); // so next time we parse, '*' inside the definition of rv_mult() won't turn into rv_mult().
	}
	
	/* reparse again - now without loops: */
	rv_parser.clear();
	if( !parse_side(SIDE0, side0_fpath) || !parse_side(SIDE1, side1_fpath) )
	  return RVIntStatus(1, DBG_INFO, DBG);

	if(DBG) rv_errstrm << DBG_INFO << "after convert_loops - propagate types\n";

	if( !rv_type_prop.process_all(rv_parser.get_parsetree(0),0) ||
		!rv_type_prop.process_all(rv_parser.get_parsetree(1),1) )
		return RVIntStatus(1, DBG_INFO, DBG);
	//
	if(DBG) rv_errstrm << DBG_INFO << "after convert_loops - call graph\n";
		
	find_arrays();	
  
	if( !create_call_graph(0, arrays_to_uas) || !create_call_graph(1, arrays_to_uas) )
	  return RVIntStatus(1, DBG_INFO, DBG);

	if(DBG) rv_errstrm << DBG_INFO << "after convert_loops - propagate ArgTypes\n";

	RVArgTypesDfs arg_types_dfs2;
	arg_types_dfs2.propagate_argtypes(rv_parser.side_parsetree, main_name);

	/* we may have added read/write globals to funcnodes: */
	sort_global_vectors(0);
	sort_global_vectors(1);
	
   /* end loops_to_rec */

  if(DBG) rv_errstrm << DBG_INFO << "P5 - after loop_to_rec\n";

  if( m_fufSet == BY_USER || m_fufSet == AUTOSET )
	if( !rv_ufs.read_fuf_file(fullPath(fuf_fname)) && m_fufSet == BY_USER)
	  return RVIntStatus(1, DBG_INFO, DBG);

  if(DBG) rv_errstrm << DBG_INFO << "P5.1 - after fuf file processing\n";

  std::ifstream tmp_auf_file;
  std::string tmp_auf_name = fullPath(base_name, RV_AUF_EXT);

  tmp_auf_file.open(tmp_auf_name.data());

  if (tmp_auf_file.is_open()) {
	rv_errstrm  << "NOTE : using auf file " << tmp_auf_name << " (causes skipping detect_equal_prototypes)\n";
	*m_pLog << "NOTE : using auf file " << tmp_auf_name << " (causes skipping detect_equal_prototypes)\n";
		
	if( !rv_ufs.read_auf_file(tmp_auf_name) ) 
	  return RVIntStatus(1, DBG_INFO, DBG);
  }

  if(DBG) rv_errstrm << DBG_INFO << "P5.2 - after auf file procesing\n";

  if( rel_fname != "" ) {
	if( !rv_ufs.read_rel_file(fullPath(rel_fname)) )
	  return RVIntStatus(1, DBG_INFO, DBG);
  
	if( !relate_globals_from_rel_file() )
	  return RVIntStatus(1, DBG_INFO, DBG);
  }

  if(DBG) rv_errstrm << DBG_INFO << "P6 - after rel file processing \n";

  /* to detect equal external relations of functions we must know equal globals: */ 
  relate_globals_of_same_name();

  rv_ufs.set_main_name(main_name);
  rv_ufs.connect_all( rv_parser.side_parsetree );		

  if(DBG) rv_errstrm << DBG_INFO << "P7 - after connect all\n"; 

  *m_pLog << "\n\n\n Syntactically equivalent \n";
  *m_pLog << "------------------------------------------------------\n";

  rv_ufs.visitAllFunctions(rv_parser, decision_params.extern_funcs_are_ufs);
 
  *m_pLog << "------------------------------------------------------\n";

  if(DBG) rv_errstrm << DBG_INFO << "P7.1 - after first pairing of equal prototypes\n"; 

  /* after we related as many globals as possible: */
  filter_common_read_only_globals(); 

  if(DBG) rv_errstrm << DBG_INFO << "P7.2 - after we relate globals\n"; 

  /*if (RVGlob::getArrHooks().array_vec0.size()) {
	 RVGlob::getArrHooks().prt_array_vec(0,2);
	 RVGlob::getArrHooks().prt_array_vec(1,2);
  }*/
  
  if( use_sem ) {
	if(DBG) rv_errstrm << DBG_INFO << "before execution of semchks \n";

	/* DIMA extract to under an option */
  
	rv_commands.mkdir(semchk_dir);

	*m_pLog << "\n\n\n Semantic Checks Results \n";
	*m_pLog << "------------------------------------------------------\n";
 
	/* DIMA_XXX extract to under an option */
	list<Edge> edges0, edges1;
	list<Match> mapf;
	list<int> syntacticEquiv0, loopFuncs0, loopFuncs1;
	vector<string> names0, names1;
	rv_ufs.prepareDecompositionData(rv_parser.get_parsetree(SIDE0), rv_parser.get_parsetree(SIDE1), 
									edges0, edges1, 
									mapf, 
									syntacticEquiv0, 
									names0, names1,
									loopFuncs0, loopFuncs1);
	prepareFuncCallCountAnalyses(rv_parser, names0, names0);
	RVT_Decompose decomposer;
	
	decomposer.Decompose_main(names0.size(), names1.size(), 
							  edges0, edges1, 
							  loopFuncs0, loopFuncs1,
							  mapf, 
							  syntacticEquiv0,
							  names0, names1, 
							  *this);		
  }

  return RVIntStatus(0);
}



///<summary>
/// The real main() of RVT
///</summary>
int main(int argc, char *argv[])
{
  RVOptions options(argc, argv);
  return options.readyToRun() ? options.main() : options.getErrorStatus();
}
