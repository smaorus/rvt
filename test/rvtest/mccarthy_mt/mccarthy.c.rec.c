

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  f91(int  a);

int  main();

int  f91(int  a)
{
  if (a > 100)
  {
    return a - 10;
  }

  return f91(f91(a + 11));
}


int  main()
{
  int  i;
  int  res = f91(i);

  return res;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
