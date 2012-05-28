#include <string>
#include <vector>
#include <map>
#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_parse.h>
#include <rv_treecomp.h>
#include <rv_loops.h>
#include <rv_funcflags.h>
#include <rv_funcpair.h>
#include <rv_traversal.h>
#include <rv_funcnode.h>
#include "rv_etc.h"
#include "rv_glob.h"

#define RV_SECTION RV_SEC_FUNCPAIR

using namespace std;



/*  RVFuncPair functions:  */
/* ======================= */

std::ostream& operator<< (std::ostream& out, const RVFuncPair& pair)
{
	pair.print(out);
	return out;
}



class NameToId {
  typedef map<string, int> StringToIdMap;

public:
  NameToId(void) {
	 m_idCounter[0] = m_idCounter[1] = 0;
  }

  int registerSymEntry(const SymEntry *entry, const RVSide& side) {
	 return registerName(entry->name, side);
  }

  int getBiggestId(void) const {
	 return max(m_idCounter[0], m_idCounter[1]);
  }

  int getIdBySymEntry(const SymEntry *se, const RVSide& side) const {
	 return getIdByName(se->name, side);
  }
 
  int getIdByFunc(const RVFuncPair *pfp, const RVSide& side) const {
	 return getIdByName(pfp->side_name[side.index()], side);
  }

  bool doesFuncMatchToId(const RVFuncPair *pfp, const RVSide& side, int id) const {
	 return (pfp != NULL) ? getIdByFunc(pfp, side) == id : false;
  }

private:
  static string composeKey(const string& name, const RVSide& side) {
	 return side.insert_side_ufprefix(name);
  }

  int getIdByName(const string &name, const RVSide& side) const {
	 string key = composeKey(name, side);
	 StringToIdMap::const_iterator found = m_name2id.find(key);

	 if (found != m_name2id.end())
		return found->second;

	 //fatal_error((char*)"NameToId::getIdByName() got an unknown name");
	 return -1;
  }

  int registerName(const string& name, const RVSide& side) {
	 string key = composeKey(name, side);
	 StringToIdMap::const_iterator found = m_name2id.find(key);
  
	 if (found == m_name2id.end())
		return m_name2id[key] = m_idCounter[side.index()]++;

	 return found->second;
  }

  int           m_idCounter[2];
  StringToIdMap m_name2id;  
};

static NameToId nameToId;


RVDecisionParams::RVDecisionParams(void)
  : allow_different_callees(false),
	extern_funcs_are_ufs(false),
	allow_cps_in_ufs(false),
	allow_ubs(false),
	pIdsOfUfs_0(NULL),
	pIdsOfUfs_1(NULL) {
}

bool RVDecisionParams::isSymEntryAmongIds(const SymEntry *se, const RVSide& side) const {
	const std::set<int>* pIds = side.isSide0()? pIdsOfUfs_0 : pIdsOfUfs_1;
	return pIds != NULL ? pIds->find(nameToId.getIdBySymEntry(se, side)) != pIds->end() : false;
}

std::ostream& operator<< (std::ostream& out, const RVDecisionParams& rvdec) {
	rvdec.print(out);
    return out;
}

void RVDecisionParams::print(std::ostream& out) const
{
     out <<  "\n\nDECISION PARAMS                "  << std::endl;
     out <<  "-----------------------------------"  << std::endl;
     out <<  " allow_different_callees  : "         << allow_different_callees << std::endl;
     out <<  " allow_cps_in_ufs         : "         << allow_cps_in_ufs        << std::endl;
     out <<  " extern_funcs_are_ufs     : "         << extern_funcs_are_ufs << std :: endl;
     out <<  " allow_ubs                : "         << allow_ubs << std :: endl;
     /* DIMA_XXX dump *pIdsOfUfs_0 and * pIdsOfUfs_1 here */
     out <<  "-----------------------------------"  << std::endl;
 }




void RVFuncPair::print(std::ostream& out) const
{
	out <<  "\n\nNAME                 " << name                 << std::endl; 
	out <<  "-----------------------------------" << std::endl; 
	if (are_related)                 out <<  "are_realted          " << are_related          << std::endl; 
	if (equal_syntax)                out <<  "equal_syntax         " << equal_syntax         << std::endl;
	// DIMA_DEL if (needs_semantic_check)        out <<  "needs_semantic_check " << needs_semantic_check << std::endl;
	// DIMA_DEL if (done_semantic_check)         out <<  "done_semantic_check  " << done_semantic_check  << std::endl;
	if (is_equal_semantics())        out <<  "equal_semantics      " << is_equal_semantics()   << std::endl;
	// DIMA_DEL if (side0_fully_equal)           out <<  "side0_fully_equal    " << side0_fully_equal    << std::endl;
	// DIMA_DEL if (equal_if_mscc)               out <<  "equal_if_mscc        " << equal_if_mscc        << std::endl;
	// DIMA_DEL if (has_check_successor)         out <<  "has_check_successor  " << has_check_successor  << std::endl;
	if (make_uf)                     out <<  "make_uf              " << make_uf              << std::endl;
	// DIMA_DEL if (check_sons)                  out <<  "check_sons           " << check_sons           << std::endl;
	// DIMA_DEL if (diff_sons)                   out <<  "diff_sons            " << diff_sons            << std::endl;

	out <<  "\n\nside0_name           " << side_name[0]         << std::endl; 
	out <<  "+++++++++++++++++++++++++++++++++++" << std::endl; 
	(*side_func[0]).fnode.print_vectors(out,true);
	out <<  "\n\nside1_name           " << side_name[1]         << std::endl; 
	out <<  "+++++++++++++++++++++++++++++++++++" << std::endl; 
	(*side_func[1]).fnode.print_vectors(out,true);
	out <<  "-----------------------------------" << std::endl; 
}

RVFuncPair::RVFuncPair(std::string ufname, std::string s0name, std::string s1name, Location& loc)
  : FunctionDef(loc), name(ufname)
{
  side_name[0] = s0name;
  side_name[1] = s1name; 

  init();
}

RVFuncPair::RVFuncPair(std::string ufname, Location& loc)
  : FunctionDef(loc), name(ufname)
{
  side_name[0] = ufname;
  side_name[1] = ufname; 

  init();
}


RVFuncPair::RVFuncPair(const RVFuncPair& o)
  : FunctionDef(o)
{
  unsigned i;
  assert(false); // not implemented properly

  if( o.united_argtypes ) {
	nArgs = o.nArgs;
	united_argtypes = new ArgType[nArgs];
	for(i=0; i<nArgs; i++)
	  united_argtypes[i] = o.united_argtypes[i];
  }
  else
	nArgs = 0;

  name = o.name;

  for(i=0; i<2; i++) {
	side_name[i] = o.side_name[i];
	side_func[i] = static_cast<FunctionDef*>(o.side_func[i]->dup());
  }

  origin = o.origin;

  are_related = o.are_related;

  equal_syntax = o.equal_syntax;
  // DIMA_DEL needs_semantic_check = o.needs_semantic_check;
  // DIMA_DEL done_semantic_check = o.done_semantic_check;
  set_equal_semantics(o.is_equal_semantics());

  // DIMA_DEL side0_fully_equal = o.side0_fully_equal;
  // DIMA_DEL equal_if_mscc = o.equal_if_mscc;

  // DIMA_DEL has_check_successor = o.has_check_successor;

  make_uf = o.make_uf;

  // DIMA_DEL check_sons = o.check_sons;
  // DIMA_DEL diff_sons = o.diff_sons;
}


void RVFuncPair::init()
{
  nArgs = 0;
  united_argtypes = NULL;

  origin   = UNKNOWN;

  RVSide::initArray(side_func);
  are_related = false;

  equal_syntax = false;
  // DIMA_DEL needs_semantic_check = false;
  // DIMA_DEL done_semantic_check  = false;
  set_equal_semantics(false);
	
  // DIMA_DEL side0_fully_equal  = false;
  // DIMA_DEL equal_if_mscc = false;
 

  // DIMA_DEL has_check_successor = false;

  make_uf  = false;

  // DIMA_DEL check_sons = 0;
  // DIMA_DEL diff_sons  = 0;
}


RVFuncPair::~RVFuncPair()
{
  reallocUnitedArgTypes(0);
}

void RVFuncPair::reallocUnitedArgTypes(unsigned int nTypes) {
	if (has_united_argtypes()) delete[] united_argtypes;
	united_argtypes = nTypes > 0 ? new ArgType[nTypes] : NULL;
}

SymEntry* RVFuncPair::mk_side_entry(std::string _side_name)
{
  SymEntry* entry = mk_fctdecl(_side_name, NULL);
  entry->u2FunctionDef = this;
  return entry;
}


bool RVFuncPair::eq_globals(FunctionDef* f0, FunctionDef* f1, 
				            bool try_relate_by_func_expr)
{
  SymbolVector *vec0, *vec1;
  SymbolVector::const_iterator  j;

  if( f0 == f1 )
	return true;
  if( !f0 || !f1 )
	return false;
  
  if( f0->fnode.read.size() != f1->fnode.read.size() ||
	  f0->fnode.written.size() != f1->fnode.written.size() )
  {
	  if (DBG) {
		  rv_errstrm << "f0_name: " <<  f0->FunctionName()->name << " f1_name: " << f1->FunctionName()->name << "\n";
		  rv_errstrm << "returning FALSE size read.size  \n";
		  rv_errstrm << "read_size0 : " << f0->fnode.read.size()   << " read_size1:  " << f1->fnode.read.size() << "\n";
		  rv_errstrm << "written_size0 : " << f0->fnode.written.size() << " written_size1: " << f1->fnode.written.size() << "\n";
	  }
	  return false;
  }

  if( f0->fnode.read.size() == 0 || f0->fnode.written.size() == 0 )
	return true;
  
  if( try_relate_by_func_expr ) {
	RVTreeComp comp;
	comp.eq_stmt( f0, f1 ); /* used only to try to relate globals */
  }

  vec0 = &f0->fnode.read;
  vec1 = &f1->fnode.read;
  FORVEC(j,(*vec0)) {
	if( !vec1->find_related(*j) ) {
	  rv_errstrm << "Can not find related READ " << (*j)->name << "\n";
	  return false;
	}
  }

  vec0 = &f0->fnode.written;
  vec1 = &f1->fnode.written;

  FORVEC(j,(*vec0)) { 
	if( !vec1->find_related(*j) ) {
	  rv_errstrm << "Can not find related WRITE " << (*j)->name << "\n";
	  return false;
	}
  }

  return true;
}


bool RVFuncPair::connect2bodies( Project *sides[2] )
{
  if( !sides[0] || !sides[1] ) {
	rv_errstrm << "Error: In RVFuncPair::connect2bodies(): side0 or side1 is NULL.\n";
	return false;
  }

  /* search func names on both sides.             
	 check their prototypes match
	 save the bodies in FunctionDef in RVFuncPair */
	  
  RVTreeComp  comp;
  SymEntry* se0 = lookup_function(side_name[0], sides[0]);
  SymEntry* se1 = lookup_function(side_name[1], sides[1]);
  
  if( !se0 || !se1 ) {
	rv_errstrm << "Warning: In RVFuncPair::connect2bodies(): unable to find function " 
			   << name << " on side 0 or 1.\n";

	return false;
  }

  /* compare the prototypes: */
  if( se0 && se0->uVarDecl && se1 && se1->uVarDecl &&
	  comp.eq_type( se0->uVarDecl->form, se1->uVarDecl->form ) ) {
	
	/* one of the next may be NULL - but we want the other one: */
	side_func[0] = se0->u2FunctionDef; 
	side_func[1] = se1->u2FunctionDef;
  }
  else { /* if the prototypes are different: */
	are_related = false;
	return true;
  }
  
  /* compare the function body definitions and the globals they use: */
  if( !comp.eq_type( se0->u2FunctionDef->decl->form, se1->u2FunctionDef->decl->form ) 
	  || !eq_globals( se0->u2FunctionDef, se1->u2FunctionDef, true ) ) {

	are_related = false; /* functions which use diffrent globals can't be a pair */
	if( is_auto() ) 
	  return true;
	else
	{
	  rv_errstrm << "Error: functions \"" << se0->name << "\" (side 0) and \""
				 << se1->name << "\" (side 1) can't be paired: \n"
				 << "  they have different prototypes or use different global(s). (on ";
	  location.printLocation(rv_errstrm); rv_errstrm << " ) \n";
	  return false;  
	}
  }

  are_related = true;
  side_func[0] = se0->u2FunctionDef;
  side_func[1] = se1->u2FunctionDef;

  //DIMA - FUF pairs are no longer necessarily semantically equal (test
  //glob_write_only_mt). But if they are then their subtrees must be too.
  
  return true;
}

/// <summary>
/// Each argument is associated with ArgType, which is a char (set of flags), saying whether it is an input/output/array/dereferences/unknown...
/// In this function we unite them for both sides, e.g., if the 3rd argument of the mapped pair has different attributes on both sides,
/// then this function will take the union of these attributes (using binary or).
/// </summary>
bool RVFuncPair::unite_argtypes()
{
  FunctionType *proto0 = (FunctionType*)side_func[0]->decl->form;
  FunctionType *proto1 = (FunctionType*)side_func[1]->decl->form;
  ArgType at0, at1;

  nArgs = side_func[0]->fnode.nArgs;

  if( nArgs != side_func[1]->fnode.nArgs ) {
	rv_errstrm << "Internal: "<< side_name[0] <<" (side 0) and"<< side_name[1] 
		   << " (side 1)  has different number of ArgTypes: "<< nArgs 
		   << " and "<< side_func[1]->fnode.nArgs <<" accordingly.\n";
	return false;
  }

  reallocUnitedArgTypes(nArgs);

  for(unsigned i = 0; i < nArgs; i++) {

	at0 = (!proto0->args[i] || !proto0->args[i]->name) ? 0 :
	  side_func[0]->fnode.get_argtype(i); 

	at1 = (!proto1->args[i] || !proto1->args[i]->name) ? 0 :
	  side_func[1]->fnode.get_argtype(i); 

	united_argtypes[i] = at0 | at1;
  }
  
  return true;
}


ArgType RVFuncPair::get_united_argtype(unsigned i)
{
  if( united_argtypes == NULL) { // this is the case of a declaration "f(void)", frequently emitted by cil
	assert(nArgs == 0);
	return 0;
  }
  if (i > nArgs )
	fatal_error("Internal: in RVFuncPair::get_united_argtype(): argtypes == NULL || i > nArgs \n", false);

  return united_argtypes[i];
}
	

bool RVFuncPair::ok_uf_struct_param(BaseType *tp, const char *where, bool allow_ubs)
{
  StructDef  *stDefn;
  Decl       *comp;
  Type       *subType;
  bool       ok = true;
  bool       first = true; 

  stDefn = get_struct_def(tp, where);

  /* check only structs/unions */
  if( !stDefn ) {
	rv_errstrm << "Error: ok_uf_struct_param(): NULL or not struct param. in: \n" <<
	  (where ? where : "UNKNOWN") <<" \n";
	return false;
  }

  for(int i=0; i < stDefn->nComponents; i++) {  
	comp = stDefn->components[i];
	while( comp ) {

	  if( !comp || !comp->form )
	ok = false;
	  else if( is_pointer(comp->form, where, &subType) ) {
	if( !allow_ubs )
	  ok = false;
	  }
	  /* items which are not pointers can be only BaseTypes: */
	  else {
          const Type *realType = real_type(comp->form, where);
          if( !is_basetype(realType) ){
              if (realType->isBaseType()) {
                  const BaseType *baseType = static_cast<const BaseType*>(realType);
                  ok = (baseType->typemask == BT_Enum);
              }
          }
      }
	
	  if( !ok && first ) {
	if( first ) {
	  rv_errstrm << "Unsupported component type of a struct/union \n"
		"  which is an argument of uninterpreted function.\n";
	  if( !allow_ubs )
		rv_errstrm << "  Try to use the \"-dk <k>\" option.\n";
	} else
		rv_errstrm <<"Struct can't be used as argument to UF.\n";

	rv_errstrm <<"  in "<<(where ? where : "UNKNOWN")<<" struct item: ";
	comp->print(rv_errstrm, true, 0); rv_errstrm <<"\n  in struct: ";
	tp->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
	first = false;
	  }
	  if( !ok )
	return false;

	  comp = comp->next;
	}
  }

  return ok;
}

//void   RVFuncPairList::set_num_calls(RVFuncPair *pfp , int *call0 , int *call1) 
//{
//  SymbolVector::const_iterator i;
//
//  (*call0) = (*call1) = 0;
//
//  FORVEC(i, pfp->side_func[0]->fnode.callers) 
//  {
//	  if ((*i)->entry && (*i)->entry->u2FunctionDef ) {
//		  FunctionDef* func =  (*i)->entry->u2FunctionDef;
//
//		  if (func->fnode.is_needed) (*call0)++;
//	  }
//  }
//
//  FORVEC(i, pfp->side_func[1]->fnode.callers) 
//  {
//	  if ((*i)->entry && (*i)->entry->u2FunctionDef ) {
//		  FunctionDef* func =  (*i)->entry->u2FunctionDef;
//
//		  if (func->fnode.is_needed) (*call1)++;
//	   }
//  }
//  
//  //if (calls_side0 != calls_side1)
//  //rv_errstrm << "Error: In RVFuncPair::connect2bodies(): side0 or side1 is NULL.\n";
//}



bool RVFuncPair::ok_uf_param(Symbol *sym, Type *tp, const char *where, bool allow_ubs)
/* checks whether an input or output arg or global doesn't make problems
	 later when the funtion will be converted to UF. */
{
  static bool pointer_first_time = true;

  Type*       subType;

  tp = real_type(tp, where);

  switch( tp->type ) 
  {
	case TT_Base:
	  if( is_basetype(tp, (BT_Struct | BT_Union)) )
		if( !ok_uf_struct_param( (BaseType*)tp, where, allow_ubs ) )
		  return false;
	  return true;

	case TT_Pointer:
	  if( pointer_first_time && !allow_ubs ) {
			rv_errstrm << "Warning: allow UBS (-dk flag) for better check"
		   << " of functions with pointer argument(s).\n  in: "
		   << (where ? where : "UNKNOWN") << " \n";
		pointer_first_time = false;
	  } 
	  subType = real_type( ((PtrType*)tp)->subType, where );
	  if( !subType->isBaseType() && !allow_ubs ) {
	rv_errstrm << "Pointer to pointer, array or function are unsupported \n" <<
	  "  without the UBS option (-dk flag). in: "<< (where ? where : "UNKNOWN") <<" \n";
	 return false;
	  }
	  if( is_basetype(subType, (BT_Struct|BT_Union)) )
		if( !ok_uf_struct_param( (BaseType*)subType, where, allow_ubs ) )
		  return false; 
	  return true;

	case TT_Array:
	  int sz;
	  Symbol *org;

	  if (RVGlob::getArrHooks().find_sym(sym , &sz, &org, 0) != -1) {
		  if (DBG) rv_errstrm << "Array as a function argument Legal .... " << sz << "\n";
		  return true;
	  }
	  rv_errstrm << "Array as a function argument or used global is currently unsupported \n" <<
	"  in an uninterpreted function. in: " << (where ? where : "UNKNOWN") << " \n";
	  return false;

	case TT_Function:
	  rv_errstrm << "Function address as a function argument or used global is unsupported \n" <<
	"  in an uninterpreted function. in: " << (where ? where : "UNKNOWN") << " \n";
	  return false;

	default:
	  return false;
  }
}
  
bool RVFuncPair::has_ok_params(bool warn_output_only_funcs, bool ignore_globals, 
				   bool allow_ubs /*= false*/)
/* decides whether the functions can be physically transferred to UFs -
	 doesn't check equality */
{
  std::string where = side_name[0] + " (side 0)";
  FunctionType *proto0 = (FunctionType*)side_func[0]->decl->form;
  FunctionType *proto1 = (FunctionType*)side_func[1]->decl->form;
  int num_in_args = 0;
  ArgType at0, at1;

  /* We assume the functions have the same prototype and read/write to equal globals. */
  for(int i = 0; i < proto0->nArgs; i++) {

	if(!proto0->args[i] || !proto0->args[i]->name )
	  continue;    /* ignore unnamed args <<=== MAYBE return false */ 
	
	at0 = side_func[0]->fnode.get_argtype(i); 
	//if (at0 & AT_Ain || at0 & AT_Aout) continue;  // change tag: PPE
	at1 = side_func[1]->fnode.get_argtype(i);
	
	if( at0 != at1 ) {
	  rv_errstrm << "Warning: argument \""<< *proto0->args[i]->name <<"\" of function: "
		 << where <<" has argtype: "<< (int)at0 <<" \n  whereas its counterpart \" "
		 << *proto1->args[i]->name << " \" on side 1 has argtype: "<< (int)at1 << " (1=in,2=out,4=deref,8=array).\n";
	  /* <<=== MAYBE return false; */
	}

	if( at0 & AT_In )
	  num_in_args++;

	//if( at0 & AT_Array ) {
	  //rv_errstrm << "Warning: pointer argument suspected to be array. Array as a function argument or used global is currently unsupported \n" <<
	//"  in an uninterpreted function. in: " << where << " \n";
	  /* return false; <<=== This is part of the unfinished handlling of arrays. changed to warning because it fails also programs withour arrays */
	//}

	if( !ok_uf_param( proto0->args[i]->name, proto0->args[i]->form, where.data(), allow_ubs ) )
	  return false;
  }

  /* we can't return pointers from UFs (but can from TUF - allow_ubs): */
  if( (!allow_ubs && is_pointer(proto0->subType, side_name[0].data()) ) ||
	  !ok_uf_param( (Symbol *) 0, proto0->subType, where.data(), allow_ubs ) )
	return false;

  SymbolVector::const_iterator  j;
  SymbolVector *vec = &side_func[0]->fnode.read;

  if( warn_output_only_funcs && num_in_args == 0 && vec->size() == 0 )
	rv_errstrm << "Warning: function \""<< where <<"\" uses no input arguments or globals.\n";
	
  if( !ignore_globals ) 
  {
	FORVEC(j,(*vec))
	  if( !is_global_var(*j) || 
	  !ok_uf_param( (*j), get_symbol_type(*j, where.data()), where.data(), allow_ubs) ) 
	return false;
	
	vec = &side_func[0]->fnode.written;
	FORVEC(j,(*vec))
	  if( !is_global_var(*j) || 
	  !ok_uf_param( (*j), get_symbol_type(*j, where.data()), where.data(), allow_ubs) ) 
	return false;
  }

  return true;
}


bool RVFuncPair::has_cps_in_subtrees()
{
  return ((side_func[0] && side_func[0]->fnode.subtree_has_cps) || 
		  (side_func[1] && side_func[1]->fnode.subtree_has_cps));
}


bool RVFuncPair::can_compare_semantically(bool allow_ubs)
/* can we physically generate code for semantic check of this pair ? */
{
  bool rec0 = side_func[0]->fnode.recursive;
  bool rec1 = side_func[1]->fnode.recursive;

  if(  rec0 != rec1 ) {
	rv_errstrm << "Problem: "<< side_name[0] <<" (side 0) "<< (rec0 ? "is" : "is not") <<
	  " recursive but "<< side_name[1] <<" (side 1) "<< (rec1 ? "is" : "is not") <<
	  " recursive - \n  can't do semantic check on them.";
	return false;
  }

  return has_ok_params(false, true, allow_ubs);  /* <<=== FIN fix to work with UBSs. */
}


void RVFuncPair::compare_syntax()
{
  RVTreeComp comp(true);

  if( !side_func[0] || !side_func[1] ) {
	equal_syntax = false;
	return;
  }

  /* check whether the syntax is equal - if we don't know this yet. */
  if( !equal_syntax ) {
	if(DBG) rv_errstrm << "compare: " << name << "().\n";

	equal_syntax = comp.eq_stmt( side_func[0], side_func[1] );

	if (equal_syntax) 
	{
		string print_str;
		int i;

		print_str = side_name[0];

		for (i=print_str.length();i<20;i++) {
			print_str += " ";
		}

		print_str += " == ";
		print_str += side_name[1];
	}

if(DBG)  rv_errstrm << side_name[0] << (equal_syntax ? " == " : " != ") << side_name[1] 
			<< " ("<< (have_bodies()?"syntax":"bodyless") <<") \n";
  }
}


Symbol* RVFuncPair::related_other_side_global(Symbol* glob, int other_side, bool in)
{
  if( !side_func[other_side] ) {
	rv_errstrm << "RVFuncPair::related_other_side_global(): body of function \""<< name 
		   <<"\" on side "<< other_side <<" is NULL.\n";
	return NULL;
  }
  RVFuncNode*   node = &side_func[other_side]->fnode;
  SymbolVector& vec  = (in ? node->read : node->written);
  return vec.find_related(glob);
}

Decl* RVFuncPair::side_arg(int arg_num, int _side)
{
  if( !side_func[_side] ) {
	rv_errstrm << "RVFuncPair::side_arg(): body of function \""<< name 
		   <<"\" on side "<< _side <<" is NULL.\n";
	return NULL;
  }
  FunctionType *proto = (FunctionType*)side_func[_side]->decl->form;
  if( arg_num >= proto->nArgs ) {
	rv_errstrm << "RVFuncPair::side_arg(): no argument #"<< arg_num <<" in prototype"
	  " of \""<< side_name[_side] << "\" (side "<< _side <<
	  "), it has " << proto->nArgs <<" args.\n";
	fatal_error("wrong argument number",false);
  }
  return proto->args[arg_num];
}


bool RVFuncPair::decide_uf(std::ostream* print_results_to,
	                       const RVDecisionParams& params,
	                       const RVFuncPair* main_pair)
{
	// assume false by default:
	make_uf = false;

	if( !valid_pair() )
		return false;

	// Don't make a UF of checked pair:
	// Note: UF stubs of simple recursive calls are generated separately.
	if( main_pair == this )
		return false;

	assert(params.pIdsOfUfs_0 != NULL && params.pIdsOfUfs_1 != NULL );	
	return make_uf = isIdFoundInAnySet(*params.pIdsOfUfs_0, *params.pIdsOfUfs_1);
}



void RVFuncPair::set_body( FunctionDef* def, int side )
{
  side_func[side] = def;
}

bool RVFuncPair::have_bodies()
{ return( valid_pair() &&
	  side_func[0] && side_func[0]->fnode.has_body() &&
	  side_func[1] && side_func[1]->fnode.has_body() ); 
}

bool RVFuncPair::no_bodies()
{ return( valid_pair() &&
		  (!side_func[0] || !side_func[0]->fnode.has_body()) &&
	  (!side_func[1] || !side_func[1]->fnode.has_body()) ); 
}


bool RVFuncPair::is_needed()
{
  if( !valid_pair() ) {
	rv_errstrm << "Internal: RVFuncPair::is_needed() "
	  "in functions \""<< side_name[0] <<"\" (side 0) and \""<<
	  side_name[1] <<" (side 1) are not related - should check each of them separately";
	return true;
  }

  return( side_func[0]->fnode.is_needed || side_func[1]->fnode.is_needed );
}

unsigned RVFuncPair::get_func_flags(int side /*=-1*/)
{
  switch( side ) {
	case 0:
	case 1:      
	  return side_func[side]->fnode.func_flags;

	default:
	  return (side_func[0]->fnode.func_flags | side_func[1]->fnode.func_flags);
  }
}

bool RVFuncPair::isIdFoundInAnySet(const set<int>& ids_0, const set<int>& ids_1) const {
  int id0 = nameToId.getIdByFunc(this, 0), id1 = nameToId.getIdByFunc(this, 1);
  bool result0 = ids_0.find(id0) != ids_0.end();
  bool result1 = ids_1.find(id1) != ids_1.end();

  if (result0 != result1 && DBG)
	  rv_errstrm << id0 << " is " << (result0? "" : "not ") << "found among ids_0=" << Utils::containerToString(ids_0) << " while " << id1 << " is " << (result1? "" : "not ") << "found among ids_1=" << Utils::containerToString(ids_1);
  //Test mutual_alias_pe reveals a case when some function f' calls
  //a function of MSCC m', while its counterpart function f calls
  //no function from MSCC m.
  return result0 | result1;
}

/* this function is currently not in use */
///<summary>
/// Marks output i as 'abondone output', which means that we cannot prove this putput as equivalent; later we will try to prove the equivalence of the function without it.
/// return true if there is at least one more output to try.
///</summary>
bool RVFuncPair::abandone_output(int i) { // ofer
	if (i == -1) {
		abandone_retval = true; 
		goto check;
	}
	if (nArgs == 0) return false; // remove this once we get the calling function to call with -1 in case it is retval.
//	assert(i >= 0 && i < nArgs);
	if (DBG) for (unsigned int j = 0; j < nArgs; ++j) rv_errstrm << "arg " << j << " " << ((united_argtypes[j] & AT_Out) != 0) << " " << ((united_argtypes[j] & AT_Aout) != 0) << "\n";
	united_argtypes[i] &= ~AT_Out; // it is not an output
	united_argtypes[i] |= AT_Aout; // it is an abandoned output
	if (DBG) for (unsigned int j = 0; j < nArgs; ++j) rv_errstrm << "arg " << j << " " << ((united_argtypes[j] & AT_Out) != 0) << " " << ((united_argtypes[j] & AT_Aout) != 0) << "\n";

check: 
	if (!abandone_retval) return true;
	for (unsigned int j = 0; j < nArgs; ++j) if ((united_argtypes[j] & AT_Out) != 0) return true;
	return false; // no outputs left
}

bool RVFuncPair::parse_uf_qualifiers(const list<string>& tokens,
		                             const list<Location>& uflocs)
{
	bool ret = true;
	list<string>::const_iterator tokit = tokens.begin();
	list<Location>::const_iterator uflit = uflocs.begin();

	for (; tokit != tokens.end() && uflit != uflocs.end(); ++tokit, ++uflit)
		if (!tokit->compare(PARTIALLY_EQUIVALENT))
			set_equal_semantics(true);
		else if (!tokit->compare(SYNTACTICALLY_EQUAL))
			equal_syntax = true;
		//else if (!tokit->compare(MUTUALLY_TERMINATING))
		else {
			rv_errstrm << "Error: bad uninterpreted function qualifier: \"" << *tokit << "\" at: ";
			uflit->printLocation(rv_errstrm);
			rv_errstrm << "\n";
			ret = false;
		}
	return ret;
}



/*  RVFuncPairList functions:  */
/* =========================== */

RVFuncPairList rv_ufs;

RVFuncPair* RVFuncPairList::lookup(const string& name, const RVSide& side) const
{
  SymEntry *se = sideTbl[side.index()].Lookup( name );
  return se && se->u2FunctionDef ?
		  static_cast<RVFuncPair*>(se->u2FunctionDef) : NULL;
}

RVFuncPair* RVFuncPairList::lookup_valid(const string& name, const RVSide& side) const
{
  RVFuncPair *pfp = lookup( name, side );
  return pfp && pfp->valid_pair() ? pfp : NULL;
}

RVFuncPair* RVFuncPairList::lookup_have_bodies(const std::string& name, int side)
{
  RVFuncPair *pfp = lookup( name, side );
  return pfp && pfp->have_bodies() ? pfp : NULL;
}

RVFuncPair* RVFuncPairList::new_pair(std::string ufname, std::string s0name, 
					 std::string s1name, Location& loc, 
					 RVFuncPair::OriginType orig)
{
  RVFuncPair *rec, *rec1;


  rec = lookup(s0name, 0);
  rec1 = lookup(s1name, 1);

  /* if the functions already exist in auf or fuf lists: */
  if( rec || rec1 ) 
  {
	rv_errstrm << "Warning: function \"" << (rec ? s0name : s1name) << 
	  "\" (side " << (rec?0:1) << ") already exists on the UF lists.\n  referred on: ";
	loc.printLocation(rv_errstrm); rv_errstrm <<" \n";

	if(rec != rec1) {
	  rv_errstrm << "Error: but \""<<s0name<<"\" and \""<<s1name<<"\" are not "
	"paired with each other !\n";
	  return NULL;
	}

	// if its status became stronger then update origin:
	if( orig == RVFuncPair::FUF )
	  rec->origin = orig;
	return rec;
  }

  rec = new RVFuncPair(ufname, s0name, s1name, loc);
  add_rec( rec->mk_side_entry(s0name), 0);
  add_rec( rec->mk_side_entry(s1name), 1);
  rec->origin = orig;
  return rec;
}

RVBoolStatus RVFuncPairList::read_uf_file(const std::string& fname, RVFuncPair::OriginType orig)
  /* Reads the file line by line: s0_func [s1_func [qualifier1 [...]]]>
	 Create a UF record for each line and adds it to lookup tables on both sides. */
{
  RVTextFileReader reader(fname);
  list<string> tokens;
  list<Location> uflocs;

  if( !reader.is_open() ) {
	rv_errstrm << "Unable to open fuf file: \"" << fname << "\"\n";
	return RVBoolStatus(false, DBG_INFO, DBG);
  }

  RVBoolStatus ret(true);
  while(reader.readNextLineTokens(tokens, uflocs)) {
	  RVFuncPair *rec = NULL;
      if(DBG) rv_errstrm << "buf=\"" << Utils::containerToString(tokens) << "\" \n";

      if (tokens.empty())
          continue;
      string name1 = tokens.front(), name2 = name1;
      if (name1.at(0) == '`' || name1.at(0) == '%') // It's a comment line in fuf line
          continue;

      tokens.pop_front();
      if (!tokens.empty()) {
    	  name2 = tokens.front();
    	  tokens.pop_front();
      }

  	  rec = new_pair(name1, name1, name2, uflocs.front(), orig);
	  ret.assign(rec != NULL && ret, __FUNCTION__, DBG);

	  if (rec != NULL && !tokens.empty()) {
		  uflocs.pop_front();
		  uflocs.pop_front();
		  ret.assign( rec->parse_uf_qualifiers(tokens, uflocs) && ret,
				      __FUNCTION__, DBG);
	  }
  }

  return ret;
}

RVFuncPairList::RVFuncPairList() : main_pair(NULL)
{ 
}

RVFuncPairList::~RVFuncPairList()
{
  /* Must remove ( HashTbl::Delete() ) all records on one side and
	 only then let the two hash tables die. */
  
  HashTbl*    pht = &sideTbl[1];
  HashTblIter it(pht);
  SymEntry   *item, *next;

  for( next = it.begin(); (item = next); next=it.next() )
	pht->Delete(item);

}


void RVFuncPairList::visitAllFunctions(RVGlobLists& parser, 
									   bool extern_funcs_are_ufs) 
{
  bool found_new = false;
  ScopeTbl* fs0 = get_file_scope(parser.get_parsetree(0));
  ScopeTbl* fs1 = get_file_scope(parser.get_parsetree(1));

  preDetectEqualPrototypes(fs0, fs1);

  do { 
	/* collect funcs with same name and prototype on both sides: */
	found_new = detect_equal_prototypes(fs0, fs1, extern_funcs_are_ufs);

	//if( use_auf )
	  /* check which have same syntax and print the result to auf_file: */
	  rv_ufs.compare_syntax_of_all_aufs();
  // while( use_auf &&  found_new );  /* try until nothing added. */
  } while( found_new );  /* try until nothing added. */
}


void RVFuncPairList::preDetectEqualPrototypes(ScopeTbl* fs0, ScopeTbl* fs1)
{
  static bool already_run = false;
  
  HashTblIter hit(fs0->htab);
  HashTblIter hit1(fs1->htab);

  assert(!already_run);

  preDetectEqualPrototypesOnSide(fs0, 0);
  preDetectEqualPrototypesOnSide(fs1, 1);

  already_run = true;
}


// Marking functions originating from loops only at the first time
void RVFuncPairList::preDetectEqualPrototypesOnSide(ScopeTbl* fs, int side) {
  SymEntry* se;
  HashTblIter hit(fs->htab);

  
  for(se = hit.begin(); !hit.end(); se = hit.next())
	  // Marking functions originating from loops
	  if( RVLoop::is_loop_name(se->name, 0)) {
		  se->u2FunctionDef->fnode.loop_2_rec = true;
		  if (DBG) rv_errstrm << "is_loop name " << " side " << side << " : " << se->name << "\n";
	  }
}


// This function return true when a new pair is found.
// In the first time it is called we try to assign all the functions 
// that originated from loop-collapsing this property
//
bool RVFuncPairList::detect_equal_prototypes(ScopeTbl* fs0, ScopeTbl* fs1,
	bool extern_funcs_are_ufs )
	// returns true when some new pair has been found.
{
	bool found_new = false;
	RVTreeComp  comp;
	RVFuncPair* rec;
	SymEntry* se0;
	SymEntry* se1;

	HashTblIter hit(fs0->htab);
	HashTblIter hit1(fs1->htab);

	for(se0 = hit.begin(); !hit.end(); se0 = hit.next())
		if( valid_function(se0) && !lookup(se0->name, 0) ) {
			// don't pair internal functions:
			if( RVParse::ignore_func(se0->name) || RVParse::supplied_by_rvt(se0->name) )
				continue;

			if(DBG) rv_errstrm << "detecting related func of: " << se0->name << "().\n";

			/* find the same function name on other side: */
			se1 = fs1->Lookup( se0->name );
			if( !se1 || !valid_function(se1) ) {
				/* try by equalTo: */
				se1 = se0->equalTo;

				if( !se1 || se1->equalTo != se0 || !valid_function(se1) )
					continue;
			}

			// don't pair internal functions:
			if( RVParse::ignore_func(se1->name) || RVParse::supplied_by_rvt(se1->name) )
				continue;

			/* if the function already exists in some UF list: */
			if( lookup(se1->name, 1) )
				continue;

			if( !extern_funcs_are_ufs && 
				(!function_has_body(se0) || !function_has_body(se1)) ) {
					rv_errstrm << "Function \"" << se0->name << "\" is bodyless (on one or both sides) - "
						" read/written globals are unknown.\n"
						"  Can't assume to be paired functions (use -extufs to force).\n";
					continue;
			}

			/* compare their prototypes: */
			if( !comp.eq_type( se0->u2FunctionDef->decl->form, se1->u2FunctionDef->decl->form ) ) {
				if (DBG) {
					rv_errstrm << "Functions side0: \"" << se0->name   << " \" \n          side1 : \" " << se1->name 
						<< " \" \nhas different prototype on different sides - invalid pair.\n";
				}
				// ofer: This code is part of an attempt to force mapping between functions even if their interface is not the same (change tag: PPE). Currently abandoning this because not clear if this can really help anywhere. 
				// very primitive implementation. Should have it in one function: sorting the names first, and then compare going up the laddar. currently complexity is param1 * param2 * 2
				/*if (!comp.eq_type_loose(se0->u2FunctionDef, se1->u2FunctionDef)) 
				continue;
				if (!comp.eq_type_loose(se1->u2FunctionDef, se0->u2FunctionDef)) 
				continue;				*/
				continue;
			}

			if( !RVFuncPair::eq_globals( se0->u2FunctionDef, se1->u2FunctionDef, true ) ) {
				if (DBG) {
					rv_errstrm << "Functions  side0: \"" << se0->name   << "\" \n           side1 : \" " << se1->name 
						<< "\" \nrefer differently to globals on different sides - invalid pair.\n";
					se0->u2FunctionDef->fnode.read.print("side 0 directly read globals: ",rv_errstrm);
					se0->u2FunctionDef->fnode.written.print("side 0 directly written globals: ",rv_errstrm);
					se1->u2FunctionDef->fnode.read.print("side 1 directly read globals: ",rv_errstrm);
					se1->u2FunctionDef->fnode.written.print("side 1 directly written globals: ",rv_errstrm);
				}
				continue;
			}

			if(DBG) rv_errstrm << "detected related pair: "<< se0->name <<" and "<< se1->name <<" .\n";

			//The allocation at the next line is never freed. It is assigned to SymEntry::u2FunctionDef,
			//which is a union member. This mem.leak occurss many times. Nevertheless, I am reluctant to modify the code of ctool.
			rec = new RVFuncPair( se0->name, se0->name, se1->name, se0->u2FunctionDef->location );
			rec->origin   = RVFuncPair::AUTODETECT;
			rec->equal_syntax = false;        /* while we don't know otherwise */
			rec->are_related = true;
			rec->set_body( se0->u2FunctionDef, 0);
			rec->set_body( se1->u2FunctionDef, 1);

			// If these are loops converted to funcs:
			if( RVLoop::is_loop_name(se0->name, 0) &&
				RVLoop::is_loop_name(se1->name, 1) ) {
					// Mark them ffNoNullArg - all arguments point to original vars:
					se0->u2FunctionDef->fnode.func_flags |= ffNoNullArg;
					se1->u2FunctionDef->fnode.func_flags |= ffNoNullArg;
			}

			add_rec( rec->mk_side_entry(se0->name), 0);
			add_rec( rec->mk_side_entry(se1->name), 1);
			found_new = true;
		}

		return found_new;
}

void RVFuncPairList::add_rec( SymEntry* rec, int side )
{
  sideTbl[side].Insert(rec);
}

bool RVFuncPairList::del_pair(RVFuncPair*  pfp)
  // returns true when the pair exists in *both* sideTbls
{
  SymEntry *se0 = sideTbl[0].Lookup(pfp->side_name[0]);
  SymEntry *se1 = sideTbl[1].Lookup(pfp->side_name[1]);


  return(se0 && se1);
}

bool RVFuncPairList::del_pair(SymEntry *se0,SymEntry *se1)
{
  if( se0 && se1 && se0->u2FunctionDef != se1->u2FunctionDef ) {
	rv_errstrm << "Internal: RVFuncPairList::del_pair(): se0 ("<< se0->name <<
	  " and se1 ("<< se1->name <<") does not point to the same RVFuncPair.";
	return false;
  }
	  
  if( se0 )
	sideTbl[0].Delete(se0);
  if( se1 )
	sideTbl[1].Delete(se1);
  return true;
}


bool RVFuncPairList::connect_all( Project *sides[2] )
{
  HashTbl*     pht = &sideTbl[1];
  HashTblIter  it(pht);
  RVFuncPair*  pfp;
  SymEntry*    item;
  bool         ret = true;

  for(item = it.begin(); !it.end(); item = it.next()) {
	pfp = (RVFuncPair*)item->u2FunctionDef;
	ret = pfp->connect2bodies( sides ) && ret;
  }

  return ret;
}


void RVFuncPairList::compare_syntax_of_all_aufs()
{
  HashTbl*    pht = &sideTbl[1];
  HashTblIter it(pht);
  RVFuncPair*  pfp;
  SymEntry*    item;

  for(item = it.begin(); !it.end(); item = it.next()) {
	pfp = (RVFuncPair*)item->u2FunctionDef;
	//DIMA_XXX if( pfp->origin == RVFuncPair::FUF )  /* later compare only AUTODETECT <<=== */
	//DIMA_XXX   continue;
	//Skipping functions from FUF bothers mutual termination checks as it receives the list of partial equivalent functions thru a FUF file
	//The two lines above were commented out in submission #79. Uncommenting them causes failure of tests mt1 & mutual1.
    if (!pfp->equal_syntax)
	    pfp->compare_syntax();
  }
}

bool RVFuncPairList::decide_ufs_fname(const std::string& flname,
			                          const RVDecisionParams& params,
			                          const RVFuncPair* main_pair)
{
  bool ret = true;
  
  std::ofstream auf_file;
  if( flname != "" ) {
	auf_file.open(flname.data());

	if( auf_file.is_open() ) {
	  decide_ufs_fstrm( &auf_file, params, main_pair );
	  auf_file.close();
	  return true;
	}
	else {
	  rv_errstrm << "Unable to open auf output file: \"" << flname << "\"\n";
	  ret = false;
	  // report failure - but compare anyway
	}
  }
  
  // no auf file
  decide_ufs_fstrm( NULL, params, main_pair );
  return ret;
}

void RVFuncPairList::decide_ufs_fstrm(std::ostream* print_results_to,
				                      const RVDecisionParams& params,
				                      const RVFuncPair* main_pair)
{
  HashTbl*    pht = &sideTbl[1];
  HashTblIter it(pht);
  RVFuncPair*  pfp;
  SymEntry*    item;

  for(item = it.begin(); !it.end(); item = it.next()) {
	pfp = (RVFuncPair*)item->u2FunctionDef;
	pfp->decide_uf(print_results_to, params, main_pair);
  }
}


bool RVFuncPairList::are_related( std::string& name0, std::string& name1 )
{
  RVFuncPair *pfp = lookup_valid( name0, 0 );
  if( !pfp || pfp->side_name[1] != name1 )
	return false;
  return true;
}

bool RVFuncPairList::are_related( Expression *s0p, Expression *s1p )
{
  Location *problem_location = NULL;
 
  if( !s0p || !s1p ) {
	rv_errstrm << "RVFuncPairList::are_related() received a NULL function call name.\n";
	return false;
  }
 
  if( s0p->etype != ET_Variable )
	problem_location = &(s0p->location);
  else if( s1p->etype != ET_Variable )
	problem_location = &(s1p->location);
	
  if( problem_location ) {
	rv_errstrm << "Indirect function calls are not supported. Problem at: ";
	problem_location->printLocation( rv_errstrm );
	rv_errstrm << " .\n";
	return false;
  }

  Variable* v0 = (Variable*)s0p;
  Variable* v1 = (Variable*)s1p;
  if( !v0->name || !v1->name )
	return false;

  return are_related( v0->name->name, v1->name->name );
}


RVBoolStatus RVFuncPairList::read_fuf_file(const std::string& flname)
{
  return read_uf_file(flname, RVFuncPair::FUF);
}

RVBoolStatus RVFuncPairList::read_rel_file(const std::string& flname)
{
  return read_uf_file(flname, RVFuncPair::REL);
}


RVBoolStatus RVFuncPairList::read_auf_file(const std::string& flname)
{
  return read_uf_file(flname, RVFuncPair::AUF);
}



bool RVFuncPairList::is_uf(const string& fname, const RVSide& side) const
{
  RVFuncPair* ret = lookup_valid(fname, side);
  return ret && ret->is_uf();
}

void RVFuncPairList::set_main_name(std::string& name)
{
  main_name = name;
}

RVFuncPair* RVFuncPairList::get_main_pair()
{
  if(!main_pair && main_name != "")
	main_pair = lookup(main_name, 0);

  return main_pair;
}

HashTblIter RVFuncPairList::get_func_pair_iter(int side)
{
  if( side != 0 && side != 1 )
	fatal_error("RVFuncPairList::get_func_pair_iter() wrong side number \n", false);

  return HashTblIter(&sideTbl[side]);
}

RVFuncPair* RVFuncPairList::getFuncPairById(int id, int side, bool mustFind) const {
  const HashTbl* pht = &sideTbl[1];
  HashTblConstIter it(pht);

  for(const SymEntry *item = it.begin(); !it.end(); item = it.next()) {
	RVFuncPair* pfp = static_cast<RVFuncPair*>(item->u2FunctionDef);
	if (nameToId.doesFuncMatchToId(pfp, side, id))
	   return pfp;
  }

  if (mustFind)
      fatal_error("RVFuncPairList::getFuncPairById(): Could not find function pair by id");
  return NULL;
}

bool RVFuncPairList::isFuncPairSemanticallyEqual(int id, int side) const {
	const RVFuncPair* pfp = getFuncPairById(id, side, false);
	return pfp != NULL && pfp->is_equal_semantics() ;
}

//Prepares the necessary information for RVT_Decompose::Decompose_main()
void RVFuncPairList::prepareDecompositionData(Project *side0, // In
											  Project *side1, // In
											  list<Edge>& edges0, //Out
											  list<Edge>& edges1, //Out
											  list<Match>& mapf, //Out
											  list<int>& syntacticEquivList0, //Out
											  vector<string>& names0, //Out
											  vector<string>& names1, //Out
											  list<int>& loopFuncs0, //Out
											  list<int>& loopFuncs1 /*Out*/)
{
  ScopeTbl* fs0 = get_file_scope(side0), *fs1 = get_file_scope(side1);
  buildNameList(fs0, fs1, names0, names1, loopFuncs0, loopFuncs1); //Must be called first, because it fills NameToId
  buildEdgeList(fs0, fs1, edges0, edges1);
  
  //Fills mapf & syntacticEquivList0:
  mapf.clear();
  syntacticEquivList0.clear();
  HashTbl*    pht = &sideTbl[1];
  HashTblIter it(pht);
  RVFuncPair* pfp;

  for(SymEntry *item = it.begin(); !it.end(); item = it.next()) {
	pfp = (RVFuncPair*)item->u2FunctionDef;
	int id0 = nameToId.getIdByFunc(pfp, 0), id1 = nameToId.getIdByFunc(pfp, 1);
	if (id0 < 0 || id1 < 0) fatal_error("Internal: perhaps outdated function name in -pfp file ? ", false);
	mapf.push_back(Match(id0, id1));
	if (pfp->equal_syntax)
	   syntacticEquivList0.push_back(id0);
  }

  return;
}


//Builds NameToId database and fills the name vectors 
void RVFuncPairList::buildNameList(ScopeTbl* fs0, 
								   ScopeTbl* fs1,
								   vector<string>& names0, /*Out*/
								   vector<string>& names1, /*Out*/
								   list<int>& loopFuncs0, //Out
								   list<int>& loopFuncs1 /*Out*/)
{
  names0.clear();
  names1.clear();

  appendFuncNames(fs0, 0, names0, loopFuncs0);
  appendFuncNames(fs1, 1, names1, loopFuncs1);
}


//Finds all relevant functions, registers them in NameToId and adds to vector names
void RVFuncPairList::appendFuncNames(ScopeTbl* fs, 
									 int side, 
									 vector<string>& names, /*Out*/
									 list<int>& loopFuncs /*Out*/) const 
{
  SymEntry *seFunc;
  HashTblIter hit(fs->htab);

  for(seFunc = hit.begin(); !hit.end(); seFunc = hit.next())
	  if (funcNodeFilterForBuildingEdgeList(seFunc)) {
		  addFuncName(seFunc, side, names);
		  if (RVLoop::is_loop_name(seFunc->name, side))
			  loopFuncs.push_back(nameToId.getIdBySymEntry(seFunc, side));
	  }
}


void RVFuncPairList::addFuncName(const SymEntry *func, 
								 int side,
								 vector<string>& names /*Out*/) const
{
  int id = nameToId.registerSymEntry(func, side);
  if (names.size() <= (unsigned)id) {
	  names.reserve(max(id + 1, (int)names.size()*2));
	  names.resize(id + 1);
  }
  names[id] = func->name;
}


void RVFuncPairList::buildEdgeList(ScopeTbl* fs0, 
								   ScopeTbl* fs1,
								   list<Edge>& edges0, /*Out*/ 
								   list<Edge>& edges1 /*Out*/)
{
  if (DBG) rv_errstrm << "Entered RVFuncPairList::buildEdgeList()\n";
  edges0.clear();
  edges1.clear();

  appendCallEdges(fs0, 0, edges0);
  appendCallEdges(fs1, 1, edges1);

  for (list<Edge>::iterator lit = edges0.begin(); lit != edges0.end(); ++lit)
	 if (DBG) rv_errstrm << "Edge on side0: " << lit->item1 << "->" << lit->item2 << '\n';
  for (list<Edge>::iterator lit = edges1.begin(); lit != edges1.end(); ++lit)
	 if (DBG) rv_errstrm << "Edge on side1: " << lit->item1 << "->" << lit->item2 << '\n';
}


bool RVFuncPairList::funcNodeFilterForBuildingEdgeList(const SymEntry* se) const {
	return valid_function(se) &&
		   !RVParse::ignore_func(se->name) &&
		   /* RVT supplied functions are not obstacle for semantic check: */
		   !RVParse::supplied_by_rvt(se->name);
}


void RVFuncPairList::appendCallEdges(ScopeTbl* fs, 
									 int side, 
									 list<Edge>& edges /*Out*/) const 
{
  SymEntry *seCaller, *seCallee;
  HashTblIter hit(fs->htab);

  for(seCaller = hit.begin(); !hit.end(); seCaller = hit.next()) {
	  if (!funcNodeFilterForBuildingEdgeList(seCaller)) 
		  continue;
	  const SymbolVector &vec = seCaller->u2FunctionDef->fnode.callees;
	  for(SymbolVector::const_iterator i = vec.begin(); i != vec.end(); i++) {
		  seCallee = fs->Lookup((*i)->name);
		  if (seCallee == 0 || !funcNodeFilterForBuildingEdgeList(seCallee))
			  continue;
		  edges.push_back(Edge(nameToId.getIdBySymEntry(seCaller, side), 
							   nameToId.getIdBySymEntry(seCallee, side)));
	  }
  }
}
