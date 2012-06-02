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


class RVRenameTree;


class RVSemChecker: public RVMain {
private:
	RVTemp m_temps;
	RVFuncPair   *m_mainPair;
	bool          m_boundedMemchkUsed;

public:
	RVSemChecker(const RVMain&);
	virtual ~RVSemChecker();

	RVCommands::ResCode check_semantic_equivalence(int f0_id, const std::set<int> idsOfUfs[2]);
	const RVFuncPair* getMainPair(void) const { return m_mainPair; }

private:
	RVSemChecker(void) {}

	bool generate_output(const std::string& fname, const std::string& pair_name);
	void generate_channels();
	void start_generation(bool gen_channels);
	bool print_global_decls(const RVRenameTree* ren0, const RVRenameTree* ren1);
	RVRenameTree *prepare_side(const RVSide& side, const std::string& side_fpath,
				               RVFuncPair* semchk_pair, bool check_cps, bool recursive);
	void warnBoundedMemchkUsed(void);
};

#endif /* RV_SEMCHECKER_H_ */
