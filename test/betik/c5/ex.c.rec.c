

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
void  f(void  *a);

int  main();

void  f(void  *a)
{
  *((int *) (a)) = 9;
}


int  main()
{
  int  a;

  f(&a);
  return a;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
