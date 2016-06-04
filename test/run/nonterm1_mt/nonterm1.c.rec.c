

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  infiniteLoop(int  x, int  y);

int  main();

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

  return 0;
}



int  main()
{
  int  a;
  int  b;
  int  res;

  res = infiniteLoop(a,b);
  return res;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
