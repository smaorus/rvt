/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "/cygdrive/c/NewRVT/test/rvtest/gcd/gcd1.c"
# 1 "<command-line>"
# 1 "/cygdrive/c/NewRVT/test/rvtest/gcd/gcd1.c"
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
  a = a;
 }
a=5;
 return b;
}



short main()
{
 short a, b;
 gcd(a,b);
 return 0;
}
