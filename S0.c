/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "/cygdrive/c/NewRVT/test/rvtest/gcd/gcd.c"
# 1 "<command-line>"
# 1 "/cygdrive/c/NewRVT/test/rvtest/gcd/gcd.c"

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

short main()
{
 short a;
 short b;
 gcd(a,b);
 return 0;
}
