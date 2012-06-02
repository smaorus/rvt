/* Constants used in Regresion Verification tool
   which may be needed by other tools (?) 
*/

#ifndef RV_CONSTS_H
#define RV_CONSTS_H

#include <string>

class RVSide;

#define RV_MAX_LINE   1023
#define RV_MAX_IDENT  255

extern const char* RV_SIDE0_UFPREFIX;
extern const char* RV_SIDE1_UFPREFIX;
extern const int RV_UFPREFIX_LEN;

extern const char* RV_SIDE0_PREFIX;
extern const char* RV_SIDE1_PREFIX;
extern const int RV_PREFIX_LEN;

//#define CBMC_UBS_PREFIX  "auto_object_"  // pointers with this prefix do not need to be allocated (recursively). Can be used fot unbounded structures. 
extern const std::string UFPREFIX;


#define RV_SEMCHK0_PREFIX "chk0_"
#define RV_SEMCHK1_PREFIX "chk1_"

/* Names of structures for defining channels and check points */
#define  RV_CHANNEL_TYPE_NAME   "CHANNEL"
#define  RV_CP_TYPE_NAME     "CP"
#define  RV_DEF_CP_TYPE_NAME "DCP"
  /* ^ for check points which use the default channel */
#define RV_SIDE0_CP_BLOCK "SIDE0_CHECK_POINTS"
#define RV_SIDE1_CP_BLOCK "SIDE1_CHECK_POINTS"
#define RV_SIDE0_FF_BLOCK "SIDE0_FUNCTION_FLAGS"
#define RV_SIDE1_FF_BLOCK "SIDE1_FUNCTION_FLAGS"
#define RV_SIDE0_SH_BLOCK "SIDE0_SHAPE_ASSUMES"
#define RV_SIDE1_SH_BLOCK "SIDE1_SHAPE_ASSUMES"

#define RV_FF_TYPE_NAME "FF"

#define RV_DEF_CHANNEL_NAME "RV_DEF_CHANNEL"

#define RV_OUTPUT_EXT ".rv.c"
#define RV_AUF_EXT    ".auf"
#define RV_LOOPS_TO_REC_EXT ".rec.c"
// used in localize lane: 
#define RV_LOCAL_PREFIX "local"
//Qualifiers of matched function pairs (in map_func):
extern const std::string PARTIALLY_EQUIVALENT;
extern const std::string SYNTACTICALLY_EQUAL;
extern const std::string MUTUALLY_TERMINATING;

// loops are made into external functions but without the recursive call
#define LOOPS_NOT_RECURSIVE

/* params for defining RV channels: */
extern const char *RVRECORD;


/* loop to recursion consts: */
extern const std::string LOOP_PREFIX;
extern const std::string LOOP_RETVAR;
extern const std::string LOOP_CONTINUE;
extern const std::string LOOP_BREAK;
extern const std::string LOOP_REF_PREFIX;
extern const char* LOOP_DEREF_PREFIX;

extern const RVSide &NO_SIDE, &SIDE0, &SIDE1;

/* loop termination codes: */ 
#define LTC_NORMAL  0
#define LTC_RETURN  123


/* Uninterpreted array related consts:*/
#define RV_S0_UA_PREFIX "rvuas0_"
#define RV_S1_UA_PREFIX "rvuas1_"
#define RV_COMMON_PREFIX "rvua_"

#define RV_DIFF_AU_SUFFIX "_diff_array_items"

#define RV_AU_DATA_PREFIX "uad_"

extern const int RV_VOID_PTR_SIZE;
#endif /* RV_CONSTS_H */
