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
  b = (b%a);
  swap(&b,&a); // note that we swapped a and b. This works only with 'refined, since it keeps swap interpreted. 
  a = a;
 }

 return b - 1;
}

void  simplify(short  *numerator_p, short  *denominator_p)
{
 short  tmp = gcd(*numerator_p, *denominator_p);
 *numerator_p = *numerator_p / ++tmp;
 *denominator_p = *denominator_p / tmp;
}



short  main()
{
 short  b, a;
 a = 0 + rv_getchar(); // the 0+ just so it won't be equal syntactically
 b = rv_getchar(); 
 simplify(&a,&b);
 return 0;
}
