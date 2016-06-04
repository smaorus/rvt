

int  f(int  x);

int  main();

int  f(int  x)
{
  int  n;

  if (x <= 1)
    return x;
  n = x >> 1;
  if (x % 2)
    n = 6 * n + 4;
  return f(n);
}


int  main()
{
  int  i;
  int  result;

  result = f(i);
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
