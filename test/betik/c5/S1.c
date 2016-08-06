/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./retarr1.cil.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./retarr1.cil.c"



int arr[5] ;
int *ptr ;
int *getarr(int *a )
{

  {
  return (a);
}
}

int main()
{ int *tmp ;
  int *__cil_tmp4 ;
  int arr_loc[5] = {1, 2};

  {
  __cil_tmp4 = arr_loc;
  tmp = getarr(__cil_tmp4);
  return *++tmp;
}
}
