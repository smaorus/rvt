#include "rv_declarations.h"

/*** global declarations of both sides: ***/
typedef struct B {
  int  a;
  struct B  *next;
} B_t;

/*** global declarations side 0: ***/
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
void  rvs0_g(B_t  *pb, B_t  *src, int  c);
int  rvs0_main();
unsigned char  chk0_Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb);
void  __CPROVER_assume(_Bool  rv_arg_2);

/*** global declarations side 1: ***/
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
void  rvs1_g(B_t  *pb, B_t  *src, int  c);
int  rvs1_main();
unsigned char  chk1_Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb);
void  __CPROVER_assume(_Bool  rv_arg_3);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
unsigned char  chk0_Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb)
{
  __CPROVER_assume(rvp_pb != 0);
  __CPROVER_assume(rvp_cur != 0);
  if (!((*rvp_cur)->a != 0))
  {
    return 0;
  }

  {
    (*rvp_pb)->a += 1;
    *rvp_cur = (*rvp_cur)->next;
  }

  return 0;
}


/*** Functions side 1: ***/
unsigned char  chk1_Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb)
{
  __CPROVER_assume(rvp_pb != 0);
  __CPROVER_assume(rvp_cur != 0);
  if (!((*rvp_cur)->a != 0))
  {
    return 0;
  }

  {
    (*rvp_pb)->a += 2;
    *rvp_cur = (*rvp_cur)->next;
  }

  return 0;
}

