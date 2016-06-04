/* type-specific outlined function created by prependOutlineFunction() */
short rv_div_short__short_(short x, short y);
/* type-specific outlined function created by prependOutlineFunction() */
short rv_mod_short__short_(short x, short y);


float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  rv_getint();
char  rv_getchar();
void  swap(short  *a, short  *b);

short  gcd(short  a, short  b);

void  simplify(short  *numerator_p, short  *denominator_p);

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

  return b - 1;
}

unsigned char  Loop_gcd_while1(short  *rvp_a, short  *rvp_b, short  *rvp_rvretval)
{
  if( !(*rvp_a != 0) )
    return 0;

  {
    *rvp_b = rv_mod_short__short_(*rvp_b,*rvp_a);
    swap(&*rvp_a,&*rvp_b);
    *rvp_a = *rvp_a;
  }

  return 0;
}



void  simplify(short  *numerator_p, short  *denominator_p)
{
  short  tmp = gcd(*numerator_p,*denominator_p) + 1;

  *numerator_p = rv_div_short__short_(*numerator_p,tmp);
  *denominator_p = rv_div_short__short_(*denominator_p,tmp);
}


short  main()
{
  short  a;
  short  b;

  a = rv_getint() + 0;
  b = rv_getint();
  simplify(&a,&b);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
