

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  fact(int  n);

int  main();

int  fact(int  n)
{
  if (n <= 0)
  {
    return 1;
  }

  return rv_mult_int__int_(n,fact(n - 1));
}


int  main()
{
  int  n;

  return fact(n);
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
