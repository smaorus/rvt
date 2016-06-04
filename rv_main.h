#ifndef RV_MAIN_H
#define RV_MAIN_H

#include <set>
#include <vector>
#include <memory>
#include <rv_funcpair.h>
#include <rv_commands.h>
#include "rv_dbg.h"

class RVFuncPair;
class RVParse;
class RVDirectives;
class RVFuncCallCountAnalysis;

/*
  RVMain 
	the main class of the RVT (Regression Verification Tool).
	This calls is responsible for the whole verification cycle
	of the RVT; parsing of both sides, loop-to-recursion conversion,
	call graph, arguments and globals types collection,
	AUF and FUF processing, semantic checks and output generation.
*/

class RVMain
{
  private:
	RVBoolStatus abandone_output(int f0_id);

  protected:
	static const std::string UNINITED;
	std::string base_dir;
	std::string semchk_dir;
	std::string base_name;
	std::string direct_fname;	
	std::string main_name;
	std::string rel_fname;
	std::string fuf_fname;
	enum {UNSET, BY_USER, AUTOSET, SET_NO} m_fufSet;

	bool frama;
	int side0_unroll_threshold, side1_unroll_threshold;
	int side0_unwind, side1_unwind;
	bool seperate_basecase_proof;
	int basecase_unwind_threshold;

	int delta_dk;
	int semchk_timeout;

	//bool use_auf;       /* = use automatically recognized uninterpreted functions. */
	bool use_sem;       /* = use semantic check (run decision procedure) to detect UFs */
	int  dk;            /* The maximum value of ubs_depth_k during the excecution */
	int  ufs_look_back; /* how many calls back on the other side the UF searches 
			   to find simmilar inputs to generate the same output. */
	int  max_records;   /* max records in chanels and UF arrays */
	int  K;             /* equivalence check bound (0 means infinite) */

	bool loops_to_rec;    /* replace loops by recursive functions. */	
	
	bool keep_all_code;     /* keep unneeded funcs */
	bool semchk_recursive;
	bool arrays_to_uas;

	RVDecisionParams decision_params;

	bool test_ctool;     /* Only parse side 0 and print it (debug only). */

	int omega_total_bound;  /* Omega bound on -dk value for whole program. */
	
	bool unitrv; // Should we perform sem check with unitrv or cbmc. 
	
	int  ubs_depth_k;   /* how deep we unwind UBS arguments and return value. */	
	bool refined; //ofer: used in rv_decompose.cpp. Whether to keep equal but nonrecursive functions interpreted.
	char completeness; // ofer: level of comppleteness, given by the user. Default is 0. in various locations we can try harder to prove equivalence on the expanse of run-time.
	bool run_cil; // ofer: whether to call cil as preprocessing
	bool mutual_term_check; // whether the current run checks mutual termination
	bool m_bAbortIfUnknownCbmcErr; //whether abort execution if CBMC returns an uninterpretable result
	bool m_c99; //whether to support C99 syntax.
	SymbolVector read_only_globals[2];

	std::string side0_fpath;
	std::string side1_fpath;

	int external_inputs; // ofer: saves the max. number of rv_getint/rv_getchar invocations. This is used to decide the size of the array that implements them in rv_inputs.c
	std::ofstream* m_pLog;
	RVDirectives*  m_pDirectives;
	std::vector<RVFuncCallCountAnalysis*> m_callChainCounter;

    //Protected methods:
	void init();

	bool do_test_ctool(std::string& fname);
	RVBoolStatus parse_side(const RVSide& side, std::string& side_fpath);
	RVBoolStatus process_directives(void);
	RVBoolStatus relate_globals_from_rel_file(void);
	void relate_globals_of_same_name();
	void sort_global_vectors(int side);
	RVBoolStatus convert_loops_to_rec(bool is_basecase = false);
	RVBoolStatus create_call_graph(int side, bool collect_arrays = false);
	void filter_common_read_only_globals();

	bool find_arrays();  
	bool do_last(const std::string& fname);	
	void preprocess(std::string& S0, std::string& S1);
	std::string fullPath(const std::string& fname, const char *ext = NULL) const;
	void prepareFuncCallCountAnalyses(const RVGlobLists& parser,
			                          const std::vector<std::string>& mapf0,
			                          const std::vector<std::string>& mapf1);
	void prepareFuncCallCountForSide(const RVGlobLists& parser,
									 const RVSide& side,
				                     const std::vector<std::string>& mapfside);
	unsigned countMaxCallChainFromTo(const RVSide& side,
			                         const std::string& from,
			                         const std::string& callee);
  public:

	RVMain(void);
	virtual ~RVMain() {}

	RVIntStatus main(void);

	RVBoolStatus eliminateGotoStatements();


	void set_K(int k) {if (k > K) K = k;}
	bool is_refined() const {return refined;}
	char get_completeness() const { return completeness;}
	bool is_checking_partial_equiv(void) const { return !mutual_term_check; }

	RVDirectives& accessDirectives(void) const { return *m_pDirectives;	}

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
	unsigned countMaxCallChain(const RVSide& side,
			                   const std::string* pFromFunc,
			                   const std::string& callee);
	RVBoolStatus reprocessAfterGotoElimination();

	void saveGotolessFiles( std::string side1_no_gotos, std::string side0_no_gotos );
	RVBoolStatus reprocessGotolessFiles( std::string side1_no_gotos, std::string side0_no_gotos );

};

#endif /* RV_MAIN_H */
