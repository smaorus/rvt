

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  *g;
void  f();

int  main();

void  f()
{
  *g = 2;
}


int  main()
{
  int  a;

  g = &a;
  f();
  return a;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
