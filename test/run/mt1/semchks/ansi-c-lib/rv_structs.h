/* Defines the structures for the user to define channels and check
   points in the spec file.
*/

#ifndef RV_STRUCTS_H
#define RV_STRUCTS_H

/*
NOTE: currently all data is passed as strings. 
      maybe later we make it structured.  <<=== decide.
*/

typedef struct {
  int item_size; /* currently unused */
} CHANNEL;


typedef struct {
  CHANNEL*       channel;
  int            cond;
  unsigned long  val;
} CP;

typedef struct {
  int            cond;
  unsigned long  val;
} DCP;

CHANNEL RV_DEF_CHANNEL = { sizeof(unsigned long) };

typedef unsigned FF[]; /* function flag */
#include <rv_funcflags.h>

/* defines for the Shape assume blocks: */
#define ASSUME(EXPR) __CPROVER_assume(EXPR)
#define SET(ASSIGN)  ASSIGN

#define NUM_SHAPE_NONDETS  5
#define MAYBE0_SET(ASSIGN) if(RV_SHAPE_NONDET[0]) { ASSIGN; }
#define MAYBE1_SET(ASSIGN) if(RV_SHAPE_NONDET[1]) { ASSIGN; }
#define MAYBE2_SET(ASSIGN) if(RV_SHAPE_NONDET[2]) { ASSIGN; }
#define MAYBE3_SET(ASSIGN) if(RV_SHAPE_NONDET[3]) { ASSIGN; }
#define MAYBE4_SET(ASSIGN) if(RV_SHAPE_NONDET[4]) { ASSIGN; }

#define INPLIES(A,B)  (!(A) || (B))  /* A -> B */

#endif /* RV_STRUCTS_H */
