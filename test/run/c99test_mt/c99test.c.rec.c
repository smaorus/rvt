

int  checkInput(int  n);

int  f(int  n);

int  main();

int  checkInput(int  n)
{
  return (n >= 0) ? (1) : (0);
}


unsigned char  Loop_f_for1(int  n, int  *rvp_i, int  *rvp_sum, int  *rvp_rvretval);


int  f(int  n)
{
  int  rvretval = 0;

  if (checkInput(n))
    return 0;
  int  i;
  int  sum = 0;
  {
    i = 1;
    Loop_f_for1(n,&i,&sum,&rvretval);
  }

  return sum;
}

unsigned char  Loop_f_for1(int  n, int  *rvp_i, int  *rvp_sum, int  *rvp_rvretval)
{
  if( !(*rvp_i < n) )
    return 0;

    *rvp_sum += *rvp_i;
  ++*rvp_i;
  return 0;
}



int  main()
{
  int  n;
  int  sum = f(n);

  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
