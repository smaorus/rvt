

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  A(int  m, int  n);

int  main();

int  A(int  m, int  n)
{
  if (m > 0 && n == 0)
  {
    return A(m - 1,1);
  }

  if (m == 0)
  {
    return n + 1;
  }

  return A(m - 1,A(m,n - 1));
}


int  main()
{
  int  x;
  int  y;

  return A(y,x);
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
