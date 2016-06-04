

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
void  __CPROVER_assume(_Bool  rv_arg_2);
void  assert(_Bool  rv_arg_3);
void  bubble_sort(int  *a, int  sz);
int  a[5];
void  bubble_sort(int  *a, int  sz);

int  init_array(int  n);

int  main();

unsigned char  Loop_bubble_sort_for1(int  *a, int  sz, int  *rvp_i);

unsigned char  Loop_bubble_sort_for1_for1(int  *a, int  i, int  *rvp_j);


void  bubble_sort(int  *a, int  sz)
{
  int  i;
  int  j;
  int  t;

  {
    i = sz - 1;
    Loop_bubble_sort_for1(a,sz,&i);
  }

}

unsigned char  Loop_bubble_sort_for1(int  *a, int  sz, int  *rvp_i)
{
  int  j; /* was originally declared outside but is used inside the loop only */
  int  t; /* was originally declared outside but is used inside the loop only */
  if( !(*rvp_i > 0) )
    return 0;

  {
    {
      unsigned char  rv_ltc_val;

      j = 0;
      rv_ltc_val = Loop_bubble_sort_for1_for1(a,*rvp_i,&j);
    }

    *rvp_i = *rvp_i - 1;
  }

  {
    return Loop_bubble_sort_for1(a,sz,rvp_i);
  }
  return 0;
}

unsigned char  Loop_bubble_sort_for1_for1(int  *a, int  i, int  *rvp_j)
{
  int  t; /* was originally declared outside but is used inside the loop only */
  if( !(*rvp_j < i) )
    return 0;

  {
    __CPROVER_assume(*rvp_j < 4 && *rvp_j >= 0);
    if (*(a + *rvp_j) < *(a + *rvp_j + 1))
    {
      t = *(a + *rvp_j);
      *(a + *rvp_j) = *(a + *rvp_j + 1);
      *(a + *rvp_j + 1) = t;
    }

    *rvp_j = *rvp_j + 1;
  }

  {
    return Loop_bubble_sort_for1_for1(a,i,rvp_j);
  }
  return 0;
}



int  init_array(int  n)
{
  *(a + 0) = 17;
  *(a + 1) = 9;
  *(a + 2) = 7;
  *(a + 3) = 11;
  *(a + 4) = 16;
  return 0;
}


int  main()
{
  int  i;

  i = init_array(5);
  bubble_sort(a,5);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
