

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
struct list {
  struct list  *next;
  int  num;
} *listvar;
void  f();

int  main();

void  f()
{
  listvar = (void *) (0);
}


int  main()
{
  f();
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
