/*
 * rv_semchecker.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: edima
 */

#include <rv_error.h>
#include <rv_consts.h>
#include <rv_macros.h>
#include <rv_etc.h>
#include "rv_semchecker.h"
#include <rv_gen.h>
#include "rv_glob.h"
#include "rv_arrays.h"
#include "rv_replace.h"
#include "rv_propagate.h"

#define RV_SECTION RV_SEC_MAIN

using namespace std;




RVSemChecker::RVSemChecker(const RVMain& o) : RVMain(o) {
	RVGlob::pushPtr(RVGlob::GLOB_RV_ARRAYS, new RVArrays(m_temps));
}

RVSemChecker::~RVSemChecker() {
	delete &rv_arrays();
	RVGlob::popPtr(RVGlob::GLOB_RV_ARRAYS);
}


class RVSemCheckResultReporter {
public:
	RVSemCheckResultReporter(const RVFuncPair* pfp, const string &semchk_dir,
			                 const string &fname, int semchk_timeout,
			                 ofstream& rv_log)
	  : m_resCode(RVCommands::ILLEGAL_ID),
	    m_pfp(pfp),
	    m_semchk_dir(semchk_dir),
	    m_fname(fname),
	    m_semchk_timeout(semchk_timeout),
	    m_rvLog(rv_log) {}


	~RVSemCheckResultReporter() {
		switch(m_resCode) {
		case RVCommands::UNKNOWN:
		  rv_errstrm << "UNKOWN result : CBMC failed compile or CTRL-C from outside "
			         << m_fname << ".rv.c) for cbmc !" "\n  ";
		  break;

		case RVCommands::UNCOMPILABLE:
		  rv_errstrm << "Internal error: RVMain::check_semantic_equivalence() generated an uncompilable file ("
		             << m_fname << ".rv.c) for cbmc !\n  (see " << m_semchk_dir << m_fname << ".gcc) \n";
		  break;

		case RVCommands::TIMEOUT:
		  rv_errstrm << "Info: RVMain::check_semantic_equivalence() reached timeout on \""
		             << m_fname << "\" (timeout = " << m_semchk_timeout <<" cpu seconds).\n";
		  break;

		case RVCommands::IO_ERROR:
		  rv_errstrm <<"Warning: failed to generate semantic check for: "<< m_pfp->side_name[0] <<"\n";
		  if(DBG) rv_errstrm << "RVMain::check_semantic_equivalence(): function pair \""
		  		             << m_pfp->name <<"\" is assumed \"semantically different\".\n";
		  //m_pfp->passed_semantic_check( false );
		  break;

		case RVCommands::SUCCESS:
		  m_rvLog << m_pfp->side_name[0] << " == " << m_pfp->side_name[1] << "\n";
		  break;

		case RVCommands::FAIL:
		  m_rvLog << m_pfp->side_name[0] << " != " << m_pfp->side_name[1] << "\n";
		  break;

		default:
		  fatal_error((char*) "RVMain::check_semantic_equivalence(): unsupported error code");
		  return;
		}
	}

	RVCommands::ResCode operator= (RVCommands::ResCode v) {
		m_resCode = v;
		return v;
	}

private:
	RVCommands::ResCode m_resCode;
	const RVFuncPair*   m_pfp;
	const string&       m_semchk_dir;
	const string&       m_fname;
	int                 m_semchk_timeout;
	ofstream&           m_rvLog;
};

RVCommands::ResCode
RVSemChecker::check_semantic_equivalence(int f0_id, const set<int> idsOfUfs[2])
{	
	RVFuncPair* pfp = rv_ufs.getFuncPairById(f0_id, 0, true);
    if (pfp == NULL)
	    return RVCommands::ILLEGAL_ID;

	std::string fname = rv_commands.combineFilePath(base_name, pfp->name); // ofer: used to include + "_" in the middle
    RVSemCheckResultReporter errcode(pfp, semchk_dir, fname, semchk_timeout, *m_pLog);
    if (is_checking_partial_equiv() && pfp->is_equal_semantics())
    	return errcode = RVCommands::SUCCESS;

	decision_params.pIdsOfUfs_0 = idsOfUfs;
	decision_params.pIdsOfUfs_1 = idsOfUfs + 1;

	bool outputGenerated = generate_output(fname, pfp->side_name[0]);

	decision_params.pIdsOfUfs_0 = NULL;
	decision_params.pIdsOfUfs_1 = NULL;

	if( !outputGenerated ) {
	    //pfp->passed_semantic_check( false );
	    return errcode = RVCommands::IO_ERROR;
	}

	if (DBG) rv_errstrm << "Semantic Check side0(" << pfp->side_name[0] << ")\tside1(" << pfp->side_name[1] << ") \n";

	bool chkres = rv_commands.run_sem_check(semchk_dir,
			                                fname,
			                                K,
			                                semchk_timeout,
			                                m_bAbortIfUnknownCbmcErr,
			                                m_c99);

	//pfp->passed_semantic_check( chkres );
	
	errcode = rv_commands.get_result();
	if (DBG) {
		string resstr("was verified to be ");
		if (chkres)
			resstr.append(mutual_term_check? "mutually terminating" : "semantically equal");
		else
			resstr.assign("failed the semantic check");
	    rv_errstrm << DBG_INFO <<"Function pair \""<< pfp->name <<"\" " << resstr << ".\n";
	}

    return chkres ? RVCommands::SUCCESS : RVCommands::FAIL;
}


bool RVSemChecker::generate_output(const std::string& fname,
				       			   const std::string& pair_name)
{
  string ofname = rv_commands.combineFilePath(semchk_dir, fname, RV_OUTPUT_EXT);
  string aufname("");
  set<string> special_func_lst;
  bool check_cps = decision_params.allow_cps_in_ufs;
  bool gen_recursive = false;

  decision_params.allow_ubs = (ubs_depth_k > 1);

  RVMainGen maingen(m_temps, rv_parser.side_parsetree, pair_name);
  maingen.set_ubs_depth(ubs_depth_k);
  maingen.set_read_only_globals(read_only_globals);
  maingen.setMain(this);

  if( !maingen.check_mains(true) ) {
	rv_errstrm << "**  Error: Can't generate calls to \""<<  pair_name
		   << "\" with appropreate arguments. \n";
	return false;
  }

  if (DBG) rv_errstrm << "generate_output(" << pair_name << ")\n";

  /* decide which pairs will be generated as UFs */
  m_mainPair = maingen.get_main_pair();
  rv_ufs.decide_ufs_fname(aufname, decision_params, m_mainPair);

  /* mark all functions which we may need in this output file: */
  RVMarkNeededDfs needed_dfs(rv_parser.side_parsetree, pair_name);

  if(DBG) rv_errstrm << DBG_INFO << "before semcheck processing: \n";

  RVFuncPair *semchk_pair = maingen.get_main_pair();
  if( semchk_pair == NULL )
	  fatal_error("Internal: in generate_output() - no semchk_pair during semantic_check !\n");

  gen_recursive = semchk_pair->side_func[0]->fnode.recursive && semchk_recursive;

  if (DBG) {
	  PRT_VAR("pair_name",pair_name);
	  rv_errstrm << DBG_INFO << "open output file and start generation.\n";
  }

  RVDischarger discharger;
  if (!m_temps.open(discharger, ofname, ios_base::out )) {
	rv_errstrm << "Error: Unable to open output file: \"" << ofname << "\"\n";
	rv_errstrm << "  for semantic function equality check of function: "<< pair_name <<" \n";
	return false;
  }

  m_temps.set_max_records(max_records);

  start_generation( check_cps );

  if(DBG) rv_errstrm << DBG_INFO << "P24: Start print renamed version of each side: \n";

  RVRenameTree *ren[2] = {NULL, NULL};

  m_temps.flush();

  /* prepare side: rename all identifiers: */
  ren[0] = prepare_side(0, side0_fpath, semchk_pair, check_cps, gen_recursive);
  discharger.addDischargeeHeapPtr(ren[0]);
  ren[1] = prepare_side(1, side1_fpath, semchk_pair, check_cps, gen_recursive);
  discharger.addDischargeeHeapPtr(ren[1]);

  if( NULL == ren[0] || NULL == ren[1]) {
	m_temps.close(discharger);
	return false;
  }

  m_temps.flush();

  /* print all global decelerations: */
  if( !print_global_decls(ren[0], ren[1]) ) {
	m_temps.close(discharger);
	return false;
  }

  m_temps.flush();

  /* process sides and output them renamed and with check point code to outstream: */

  {
	  bool res;
	  if (DBG) rv_errstrm << "/*** Functions side 0: ***/\n";
	  m_temps.print("\n/*** Functions side 0: ***/\n");
	  res = ren[0]->print_all(m_temps, false, true);
	  if (DBG) rv_errstrm << "/*** Functions side 1: ***/\n";
	  m_temps.print("\n/*** Functions side 1: ***/\n");
	  res = res && ren[1]->print_all(m_temps, false, true);
	  if (!res) { m_temps.close(discharger);  return false;}
  }

  m_temps.flush();

  if(DBG) rv_errstrm << DBG_INFO << "P25\n";
  /* UF generation */

  auto_ptr<RVUFGen> ufgen( mutual_term_check? new RVReUfGen(m_temps) //DIMA_REACH_EQUIV
                                            : new RVUFGen(m_temps));

  ufgen->set_rens(rv_parser.side_parsetree, ren);
  ufgen->set_ubs_depth(ubs_depth_k);
  ufgen->set_look_back(ufs_look_back);
  ufgen->set_read_only_globals(read_only_globals);
  ufgen->setMain(this);

  try {
	  ufgen->gen_ufs(decision_params.allow_cps_in_ufs); // makes equivalent descendants uninterpreted.

	  if( gen_recursive ) {
		  ufgen->gen_one_uf(semchk_pair, decision_params.allow_cps_in_ufs); // makes a recursive call uninterpreted.
	  }
	  //ren[0]->delete_parsetree(); // Could be executed automatically
	  //ren[1]->delete_parsetree(); // upon leaving this method.

	  //DIMA_REACH_EQ
	  check_cps = mutual_term_check;

	  if(DBG) rv_errstrm << DBG_INFO << "P26\n";
	  if (check_cps) ufgen->generate_aux();
	  if(DBG) rv_errstrm << DBG_INFO << "P27\n";

	  // Generating the main function
	  m_temps.print("  /* now starting main */\n");
	  m_temps.gen_main_head();
	  m_temps.separate_uf_streams();
	  maingen.gen_main(check_cps);
	  //m_temps.unite_uf_streams();  // we now unite inside gen_main

	  if(DBG) rv_errstrm << DBG_INFO << "P28\n";

	  m_temps.close(discharger);

	  if (mutual_term_check)
		  ufgen->determineLoopBackDepths(ofname, *this);

	  return true;
  } catch(RVSemCheckException e) {
	  rv_errstrm << "Aborting semantic check: " << e.getMsg() << '\n';
	  return false;
  }
}

void RVSemChecker::generate_channels()
{
  SymEntry* se;
  HashTblIter hit = accessDirectives().get_channels_iter();
  if(DBG) rv_errstrm << DBG_INFO << "generate_channels()\n";
  for(se = hit.begin(); !hit.end(); se = hit.next())
	if( RVDirectives::is_channel(se) )
	  m_temps.gen_channel( se->name );
}


void RVSemChecker::start_generation(bool gen_channels)
{
if(DBG) rv_errstrm << DBG_INFO << "enter start_generation()\n";
 // m_temps.gen_cbmc_func_headers();
	m_temps.include_rv_declarations(); // ofer: now all declarations in rv_declarations.h
	if (external_inputs > 0) {
		stringstream s;
		s << external_inputs;
		m_temps.print("#define RV_MAX_INPUTS " + s.str() +"\n");
		m_temps.print("#include \"rv_inputs.c\"");
	}

  if( gen_channels ) {
	m_temps.gen_channel_def();
  if(DBG) rv_errstrm << DBG_INFO << "after gen_channel_def()\n";
	m_temps.gen_RVCHECK();

	generate_channels();
  if(DBG) rv_errstrm << DBG_INFO << "after generate_channels()\n";
  }
 }

bool RVSemChecker::print_global_decls(const RVRenameTree* ren0, const RVRenameTree* ren1)
{
  CHK_NULL1( (ren0 && ren1), "RVMain::print_global_decls()");

  bool ret = true;

  m_temps.print("\n/*** global declarations side 0: ***/\n");
  ret = ren0->print_all(m_temps, true, false) && ret;
  m_temps.print("\n/*** global declarations side 1: ***/\n");
  ret = ren1->print_all(m_temps, true, false) && ret;
  m_temps.print("\n/*** end of global declarations side 1: ***/\n");

//  DIMA_DEL
//  const std::set<std::string>& special_func_lst = ren[0]->get_recursive_func_lst();
//
//  // Special case for the recursive calls
//  //
//
//
//  for (set<string>::const_iterator i = special_func_lst.begin(); i != special_func_lst.end(); ++i) {
//	  ret = ren[0]->print_uf_rec_decl(*i , rv_outstrm)  && ret;
//	  ret = ren[1]->print_uf_rec_decl(*i , rv_outstrm)  && ret;
//  }

   if (arrays_to_uas)
	   ret = rv_arrays().gen_prototypes() && ret;
   m_temps.print("/*** end of global declarations. ***/\n");
  return ret;
}

RVRenameTree* RVSemChecker::prepare_side(const RVSide& side,
		                               	 const string& side_fpath,
						          		 RVFuncPair* semchk_pair,
						          		 bool check_cps,
						          		 bool recursive)
  // returns the renamer after renaming - but before printed anything
{
  RVParse parser;

  if( !parser.parse_path(side_fpath, side.toString()) )
	return NULL;

  bool ret = true;
  Project *pt = parser.take_parsetree();
  RVRenameTree* ren(new RVRenameTree(pt, side));

  if( semchk_pair )
	ren->set_semchk_pair(semchk_pair, recursive);

  if( check_cps )
	ren->set_directs(&accessDirectives());

  RVTypeProp rv_type_prop("RVSemChecker::prepare_side");
  /* do type prop - mainly to fix struct component entries  */
  ret = rv_type_prop.process_all(pt, side) && ret;

  /* Note: the func names are checked thru rv_parser.is_needed(). */
  if( !keep_all_code )
	ret = ren->remove_unneeded_funcs() && ret;

  /* replace array decls and types with the UA form: */
  if (arrays_to_uas)
	ret = rv_arrays().replace_array_decls_and_types(pt, side.index()) && ret;

  ret = ren->rename_all(decision_params) && ret;

  if (ret)
	return ren;
  delete ren;
  return NULL;
}


