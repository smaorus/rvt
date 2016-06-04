

int  rv_getint();
char  rv_getchar();
void  swap(char  *a, char  *b);

char  gcd(char  a, char  b);

void  simplify(char  *numerator_p, char  *denominator_p);

char  main();

void  swap(char  *a, char  *b)
{
  char  tmp = *a;

  *a = *b;
  *b = tmp;
}


unsigned char  Loop_gcd_while1(char  *rvp_a, char  *rvp_b, char  *rvp_rvretval);


char  gcd(char  a, char  b)
{
  char  rvretval = 0;

  {
    Loop_gcd_while1(&a,&b,&rvretval);
  }

  return b - 1;
}

unsigned char  Loop_gcd_while1(char  *rvp_a, char  *rvp_b, char  *rvp_rvretval)
{
  if( !(*rvp_a != 0) )
    return 0;

  {
    *rvp_b = *rvp_b % *rvp_a;
    swap(&*rvp_b,&*rvp_a);
    *rvp_a = *rvp_a;
  }

  return 0;
}



void  simplify(char  *numerator_p, char  *denominator_p)
{
  char  tmp = gcd(*numerator_p,*denominator_p);

  *numerator_p = *numerator_p / ++tmp;
  *denominator_p = *denominator_p / tmp;
}


char  main()
{
  char  b;
  char  a;

  a = 0 + rv_getchar();
  b = rv_getchar();
  simplify(&a,&b);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
