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
  b = b%a;
  swap(&a,&b);
  a = a;
 }

 return b - 1;
}

void  simplify(short  *numerator_p, short  *denominator_p)
{
 short  tmp = gcd(*numerator_p, *denominator_p) + 1;
 *numerator_p = *numerator_p / tmp;
 *denominator_p = *denominator_p / tmp;
}



short  main()
{
 short  a, b;
 a = rv_getint() + 0; // the +0 just so it won't be equal syntactically
 b = rv_getint(); 
 simplify(&a,&b);
 return 0;
}
