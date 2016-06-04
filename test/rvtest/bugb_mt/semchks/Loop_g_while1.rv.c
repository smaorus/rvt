#include "rv_declarations.h"

/*** global declarations of both sides: ***/
enum Elem { rvs0_ELEM0, rvs0_ELEM1, rvs0_ELEM2 };
typedef struct B {
  int  a;
  char  b;
  enum Elem  c;
  struct B  *next;
} B_t;

/*** global declarations side 0: ***/
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
int  rvs0_getA(B_t  *src);
void  rvs0_g(B_t  *pb, B_t  *src, enum Elem  c);
int  rvs0_main();
unsigned char  chk0_Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb);
void  __CPROVER_assume(_Bool  rv_arg_2);

/*** global declarations side 1: ***/
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
int  rvs1_getA(B_t  *src);
void  rvs1_g(B_t  *pb, B_t  *src, enum Elem  c);
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
  if (!((*rvp_cur)->next != 0))
  {
    return 0;
  }

  {
    (*rvp_pb)->b = 0;
  }

  return 0;
}


/*** Functions side 1: ***/
unsigned char  chk1_Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb)
{
  __CPROVER_assume(rvp_pb != 0);
  __CPROVER_assume(rvp_cur != 0);
  if (!((*rvp_cur)->next != 0))
  {
    return 0;
  }

  {
    (*rvp_pb)->b = 2;
  }

  return 0;
}

