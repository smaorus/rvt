/*
 * rv_const.cpp
 *
 *  Initializations of the constant values declared in rv_const.h
 *
 *  Created on: May 10, 2011
 *      Author: edima
 */

#include <string.h>
#include <assert.h>
#include "rv_consts.h"
#include "rv_side.h"

//Notations of equivalence:
const std::string PARTIALLY_EQUIVALENT ("partially-equivalent");
const std::string SYNTACTICALLY_EQUAL  ("syntactically-equal");
const std::string MUTUALLY_TERMINATING ("mutually-terminating");

/* params for defining RV channels: */
const char* RVRECORD("unsigned long ");

/* loop to recursion consts: */
const std::string LOOP_PREFIX     ("Loop_");
const std::string LOOP_RETVAR     ("rvretval");
const std::string LOOP_CONTINUE   ("l_continue");
const std::string LOOP_BREAK      ("l_break");
const std::string LOOP_REF_PREFIX ("rvp_");
const char* LOOP_DEREF_PREFIX     ("*rvp_");

const RVSide &NO_SIDE(""), &SIDE0(0), &SIDE1(1);


static int determinePrefixLength(const char *p0, const char *p1) {
	size_t res = strlen(p0);
	assert(res == strlen(p1));
	return int(res);
}

const char* RV_SIDE0_UFPREFIX("rvs0_");
const char* RV_SIDE1_UFPREFIX("rvs1_");
const int RV_UFPREFIX_LEN = determinePrefixLength(RV_SIDE0_UFPREFIX, RV_SIDE1_UFPREFIX);

const char* RV_SIDE0_PREFIX(RV_SIDE0_UFPREFIX);
const char* RV_SIDE1_PREFIX(RV_SIDE1_UFPREFIX);
const int RV_PREFIX_LEN = determinePrefixLength(RV_SIDE0_PREFIX, RV_SIDE1_PREFIX);

const std::string UFPREFIX("__CPROVER_uninterpreted_");

const int RV_VOID_PTR_SIZE(128);
