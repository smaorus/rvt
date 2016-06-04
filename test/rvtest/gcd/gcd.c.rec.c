/* type-specific outlined function created by prependOutlineFunction() */
short rv_mod_short__short_(short x, short y);


float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
void  swap(short  *a, short  *b);

short  gcd(short  a, short  b);

short  main();

void  swap(short  *a, short  *b)
{
  short  tmp = *a;

  *a = *b;
  *b = tmp;
}


unsigned char  Loop_gcd_while1(short  *rvp_a, short  *rvp_b, short  *rvp_rvretval);


short  gcd(short  a, short  b)
{
  short  rvretval = 0;

  {
    Loop_gcd_while1(&a,&b,&rvretval);
  }

  return b;
}

unsigned char  Loop_gcd_while1(short  *rvp_a, short  *rvp_b, short  *rvp_rvretval)
{
  if( !(*rvp_a != 0) )
    return 0;

  {
    *rvp_b = rv_mod_short__short_(*rvp_b,*rvp_a);
    swap(&*rvp_a,&*rvp_b);
  }

  {
    return Loop_gcd_while1(rvp_a,rvp_b,rvp_rvretval);
  }
  return 0;
}



short  main()
{
  short  a;
  short  b;

  gcd(a,b);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
