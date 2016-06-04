

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  f91(int  x);

int  main();

int  f91(int  x)
{
  if (x < 101)
    return f91(f91(11 + x));
  return x - 10;
}


int  main()
{
  int  i1;
  int  res1 = f91(i1);

  return res1;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
