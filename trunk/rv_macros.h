/* Macros used in all parts of RVT source code: */

#ifndef RV_MACROS_H
#define RV_MACROS_H

#include "rv_dbg.h"

/* vector for loops: */
#define FORVEC(IT,VEC)   for((IT)=(VEC).begin(); (IT)!=(VEC).end(); ++(IT))
#define FORVEC_IN(IT,VEC)   for(unsigned int IT = 0; j < (VEC).size(); ++IT)

#define FORIT(ITEM,ITER) for((ITEM)=(ITER).begin(); !(ITER).end(); (ITEM)=(ITER).next()) 

#define FORINT(C,it,v) for(C<int>::const_iterator it = v.begin(); it != v.end(); ++it)

#ifndef THIS
#define THIS (*this)
#endif

#define ARRAY_LEN(A) (sizeof(A)/sizeof((A)[0]))


/* recourse into field F on both sides: */  
#define PROC(F)  {if(!process(s0p->F)) {if(DBG) tryRepProcBreakpoint("PROC", DBG_INFO); return false;} }

/* process only if F is not NULL: */
#define TRY_PROC(F)  {if(s0p->F!=NULL && !process(s0p->F)) {if(DBG) tryRepProcBreakpoint("TRY_PROC", DBG_INFO); return false;}}

/* the versions with try_replace(): */
#define REP_PROC(F)  {if(try_replace(&(s0p->F)) && !process(s0p->F)) {if(DBG) tryRepProcBreakpoint("REP_PROC", DBG_INFO);  return false;}}
#define TRY_REP_PROC(F)  \
  {if(s0p->F!=NULL && try_replace(&(s0p->F)) && !process(s0p->F)) {if(DBG) tryRepProcBreakpoint("TRY_REP_PROC", DBG_INFO); return false;}}

#define CHK_NULL(WHERE) \
  {if(s0p == NULL){rv_errstrm<<"Error: "<<(WHERE)<<" got NULL value.\n"; /*return false;*/}}

#define CHK_NULL_BOOL(WHAT,WHERE) \
  {if(!(WHAT)){rv_errstrm<<"Error: "<<(WHERE)<<" got NULL value.\n"; return RVBoolStatus(false, WHERE, DBG);}}

#define CHK_NULL1(WHAT,WHERE) \
  {if(!(WHAT)){rv_errstrm<<"Error: "<<(WHERE)<<" got NULL value.\n"; return NULL;}}

/* chenge the type of the pointers that are used for the sides to T: */
#define RETYPE(T)  T *tmp_it=((T*)s0p); T *s0p=tmp_it; 
//  if(DBG){rv_errstrm<<"RETYPE: "<<#T<<"\n";}

#if 1
#define BY(by) "\t/* Generated by:  " << by << "/ " << __FILE__ << ":" << __LINE__ << "*/\n"
#else
#define BY(by) "\n"
#endif

/* fix BT_NoType and BT_Enum types to be standard int types: */
#define FIX_INT_MASK(M) \

#ifndef RVDELETE
	#define RVDELETE(p) delete (p)
	#define RVDELARR(a) delete[] (a)
#endif /* RVDELETE */

#define interface struct
#define abstract

#endif /* RV_MACROS_H */
