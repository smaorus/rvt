/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./gcd.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./gcd.c"
# 1 "./rv_inputs.h" 1

int rv_getint();
char rv_getchar();
# 2 "./gcd.c" 2

void swap(short *a, short *b)
{
 short tmp = *a;
 *a = *b;
 *b = tmp;
}

short gcd(short a, short b)
{
 while (a != 0)
 {
  b = b%a;
  swap(&a,&b);
 }

 return b;
}

void simplify(short *numerator_p, short *denominator_p)
{
 short tmp = gcd(*numerator_p, *denominator_p);
 *numerator_p = *numerator_p / tmp;
 *denominator_p = *denominator_p / tmp;
}



short main()
{
 short a;
 short b;

 a = rv_getint();
 b = rv_getint();
 simplify(&a,&b);
 return 0;
}
