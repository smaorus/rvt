/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./retarr.cil.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./retarr.cil.c"



int arr[5] ;
int *ptr ;
int *getarr(int *a )
{ int *loc_ptr ;

  {
  loc_ptr = a;
  return (loc_ptr);
}
}

int main()
{ int arr_loc[5] = {1, 2};
  int *parr ;
  int res ;
  int *tmp ;

  {
  parr = arr_loc;
  tmp = getarr(parr);
  res = tmp[1];
  return (res);
}
}
