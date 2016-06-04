

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  n;
int  ident(int  n);

int  sum(int  n);

int  main();

int  ident(int  n)
{
  return n;
}


int  sum(int  n)
{
  n = ident(n + 1) - 1;
  if (n <= 1)
    return n;
  return n + sum(n - 1);
}


int  main()
{
  return sum(n);
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
