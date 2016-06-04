/*
 * rv_semchecker.h
 *
 *  Created on: Nov 19, 2011
 *      Author: edima
 */

#ifndef RV_SEMCHECKER_H_
#define RV_SEMCHECKER_H_

#include "rv_main.h"
#include "rv_temps.h"
#include "rv_unroller.h"


class RVRenameTree;


class RVSemChecker: public RVMain {
private:
	RVTemp m_temps;
	RVFuncPair   *m_mainPair;
	bool          m_boundedMemchkUsed;
	
public:
	RVSemChecker(const RVMain&);
	virtual ~RVSemChecker();

	RVCommands::ResCode check_semantic_equivalence(int f0_id, const std::set<int> idsOfUfs[2], std::string side0_fpath, std::string side1_fpath);
	const RVFuncPair* getMainPair(void) const { return m_mainPair; }

private:
	RVSemChecker(void) {}

	bool generate_output(const std::string& fname, const std::string& pair_name, std::string side0_fpath, std::string side1_fpath);
	void generate_channels();
	void start_generation(bool gen_channels);
	bool print_global_decls( RVRenameTree* ren0,  RVRenameTree* ren1);
	RVRenameTree *prepare_side(const RVSide& side, const std::string& side_fpath,
		RVFuncPair* semchk_pair, bool check_cps, bool recursive, rv_unroller* unroller);

	RVRenameTree* prepare_side(const RVSide& side, Project *pt, RVFuncPair* semchk_pair, bool check_cps,
		bool recursive,	rv_unroller* unroller);

	void warnBoundedMemchkUsed(void);
	std::vector<std::string>* get_all_uf_names();
	
	bool unrollingIsUsed(const std::string& fname);
	bool proveBaseCase(const std::string& pair_name, std::string side0_fpath, std::string side1_fpath );
	bool createUnrollFile(const std::string& pair_name, std::string side_fpath, int unroll_threshold, int side);
	bool createBaseCaseTestFile( const std::string& pair_name, std::string* side_paths, int* side_thresholds, int side );

	void unrollSide(int side, const std::string& pair_name, RVRenameTree * ren[2], int threshold, bool call_uf);

	bool print_function_bodies(RVRenameTree * ren[2]);
	string getUnrollFileName(string funcName, int side);
	bool checkBaseCaseEquivalence( const std::string& pair_name, int side_thresholds[2] );
};

#endif /* RV_SEMCHECKER_H_ */
