#include "rv_declarations.h"

/*** global declarations of both sides: ***/

/*** global declarations side 0: ***/
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
void  rvs0_body(int  *pX, int  *pY);
int  rvs0_infiniteLoop(int  x, int  y);
int  rvs0_main();
unsigned char  chk0_Loop_infiniteLoop_while1(int  *rvp_x, int  *rvp_y, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_2);

/*** global declarations side 1: ***/
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
int  rvs1_infiniteLoop(int  x, int  y);
int  rvs1_main();
unsigned char  chk1_Loop_infiniteLoop_while1(int  *rvp_x, int  *rvp_y, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_3);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
void  rvs0_body(int  *pX, int  *pY)
{
  __CPROVER_assume(pY != 0);
  __CPROVER_assume(pX != 0);
  if (*pX > *pY)
  {
    --*pX;
    ++*pY;
  }

  else
  {
    ++*pX;
    --*pY;
  }

}

unsigned char  chk0_Loop_infiniteLoop_while1(int  *rvp_x, int  *rvp_y, int  *rvp_rvretval)
{
  __CPROVER_assume(rvp_rvretval != 0);
  __CPROVER_assume(rvp_y != 0);
  __CPROVER_assume(rvp_x != 0);
  if (!(*rvp_x > 0 && *rvp_y > 0))
  {
    return 0;
  }

  {
    rvs0_body(&*rvp_x,&*rvp_y);
  }

  return 0;
}


/*** Functions side 1: ***/
unsigned char  chk1_Loop_infiniteLoop_while1(int  *rvp_x, int  *rvp_y, int  *rvp_rvretval)
{
  __CPROVER_assume(rvp_rvretval != 0);
  __CPROVER_assume(rvp_y != 0);
  __CPROVER_assume(rvp_x != 0);
  if (!(*rvp_x > 0 && *rvp_y > 0))
  {
    return 0;
  }

  {
    if (*rvp_y < *rvp_x)
    {
      *rvp_x = *rvp_x - 1;
      *rvp_y = 1 + *rvp_y;
    }

    else
    {
      *rvp_y = *rvp_y - 1;
      *rvp_x = -~*rvp_x;
    }

  }

  return 0;
}

