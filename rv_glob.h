/*
 * rv_glob.h
 *
 *  Created on: Nov 19, 2011
 *      Author: edima
 */

#ifndef RV_GLOB_H_
#define RV_GLOB_H_

#include <stack>

#define GLOB_UNIQ_ID RVGlobalUniqueId m_uniqId;
#define ALLOC_UNIQ_ID() m_uniqId = RVGlob::allocUniqId(sizeof(*this))


typedef unsigned long RVGlobalUniqueId;


class RVArrays;
class RvTraversal;


class RVGlob {
public:
	// Global flags: they are initialized inside the body of flags() in rv_etc.cpp
	enum flag_tag{GLBL_OUTLINE, GLBL_OUTLINE_NOW,
		GLBL_LAST_FLAG}; // do not remove/use GLBL_LAST_FLAG. It is used to determine the size of the array in flags()

	enum counter_tag{GLBL_EXTERNAL_INPUTS,
		GLBL_LAST_COUNTER}; // do not remove/use GLBL_LAST_COUNTER. It is used to determine the size of the array in counters()

	static bool flags(flag_tag, char set = -1) ;
	static int counters(counter_tag, int set = -1);


	enum RvGlobtype { GLOB_RV_ARRAYS, GLOB_ARRHOOKS, GLOB_ID_COUNTER,
		              GLOB_RV_N_ELEMS /* Must be last */
	};

	static void pushPtr(RvGlobtype typeId, void *);
	static void* popPtr(RvGlobtype typeId);

	static RVArrays& getRvArrays(void) {return *(RVArrays*) getPtr(GLOB_RV_ARRAYS);}
	static RvTraversal& getArrHooks(void) {return *(RvTraversal*) getPtr(GLOB_ARRHOOKS);}

	static RVGlobalUniqueId allocUniqId(size_t sizeofType = 0);

private:
	static void *getPtr(RvGlobtype typeId);

	static std::stack<void *> ms_globs[GLOB_RV_N_ELEMS];
};


#endif /* RV_GLOB_H_ */
