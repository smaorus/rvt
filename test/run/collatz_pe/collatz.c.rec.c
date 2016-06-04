

int  f(int  a);

int  main();

int  f(int  a)
{
  if (a > 1)
  {
    a = (a & 1) ? (3 * a + 1) : (a / 2);
    return f(a);
  }

  return a;
}


int  main()
{
  int  i;
  int  result;

  result = f(i);
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
