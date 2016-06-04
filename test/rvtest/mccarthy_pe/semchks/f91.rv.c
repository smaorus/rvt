#include "rv_declarations.h"

/*** global declarations of both sides: ***/

/*** global declarations side 0: ***/
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
int  chk0_f91(int  a);
int  rvs0_main();
int  rvs0_f91(int  a);
void  __CPROVER_assume(_Bool  rv_arg_2);

/*** global declarations side 1: ***/
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
int  chk1_f91(int  x);
int  rvs1_main();
int  rvs1_f91(int  x);
void  __CPROVER_assume(_Bool  rv_arg_3);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
int  rvs0_f91(int  a);
int  chk0_f91(int  a)
{
  if (a > 100)
  {
    return a - 10;
  }

  return rvs0_f91(rvs0_f91(a + 11));
}


/*** Functions side 1: ***/
int  rvs1_f91(int  x);
int  chk1_f91(int  x)
{
  if (x < 101)
  {
    return rvs1_f91(rvs1_f91(11 + x));
  }

  return x - 10;
}


  /* Declarations of the CBMC uninterpreted functions */
int  __CPROVER_uninterpreted_retval(int );

  /* CBMC-UF side 0: */ 
int  rvs0_f91(int  a)
{
  int  retval;

  /* Declarations: */


  /* Each output is assigned a UF:*/
  retval= __CPROVER_uninterpreted_retval(a);

  return retval;
}


  /* CBMC-UF side 1: */ 
int  rvs1_f91(int  x)
{
  int  retval;

  /* Declarations: */


  /* Each output is assigned a UF:*/
  retval= __CPROVER_uninterpreted_retval(x);

  return retval;
}

