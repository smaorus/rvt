// gcd_refine are for testing the 'refine' flag in rv_decompose. When this flag is on 
// nonrecursive equal functions are kept interpreted. This is why we need the assumptions, 
// The change from swap(&a, &b) to swap (&b, &a) in gcd_refine1 is only possible because we keep swap interpreted. 

#define short char
#include "rv_inputs.h"

void  swap(short  *a, short  *b)
{
short  tmp = *a;

 *a = *b;
 *b = tmp;
}

short  gcd(short  a, short  b)
{
 while (a != 0)
 {
  b = b % a;
  swap(&a,&b);  
 }

 return b;
}

void  simplify(short  *numerator_p, short  *denominator_p)
{
  short  tmp = gcd(*numerator_p,*denominator_p);
  *numerator_p = *numerator_p / tmp;
  *denominator_p = *denominator_p / tmp;
}



short  main()
{
 short  a;
 short  b;

 a = rv_getchar(); 
 b = rv_getchar();
 simplify(&a,&b);
 return 0;
}
