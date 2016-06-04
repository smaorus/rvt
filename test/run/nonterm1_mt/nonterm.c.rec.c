

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
void  body(int  *pX, int  *pY);

int  infiniteLoop(int  x, int  y);

int  main();

void  body(int  *pX, int  *pY)
{
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


unsigned char  Loop_infiniteLoop_while1(int  *rvp_x, int  *rvp_y, int  *rvp_rvretval);


int  infiniteLoop(int  x, int  y)
{
  int  rvretval = 0;

  {
    Loop_infiniteLoop_while1(&x,&y,&rvretval);
  }

  return x;
}

unsigned char  Loop_infiniteLoop_while1(int  *rvp_x, int  *rvp_y, int  *rvp_rvretval)
{
  if( !(*rvp_x > 0 && *rvp_y > 0) )
    return 0;

    body(&*rvp_x,&*rvp_y);
  return 0;
}



int  main()
{
  int  i;
  int  j;
  int  res;

  res = infiniteLoop(i,j);
  return res;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
