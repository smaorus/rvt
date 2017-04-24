

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  arr[5];
int  *ptr;
int  *getarr(int  *a);

int  main();

int  *getarr(int  *a)
{
  int  *const loc_ptr = a;

  return ptr;
}


int  main()
{
  int  arr_loc[5];
  int  *parr = arr_loc;
  int  res = *getarr(parr);

  return res;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
