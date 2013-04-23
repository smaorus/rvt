int arr0[5];
int *ptr0 = arr0;


int* getarr0(int *a) {
  int *const loc_ptr = a;
  return ptr0;
}


int main0() {
  int arr_loc[5] = {};
  int *parr = arr_loc;
  int res = *getarr0(parr);
  return res;
}



int arr1[5];
int *ptr1 = arr0;


int* getarr1(int* a) {
  int *loc_ptr;
  loc_ptr = a;
  return ptr1;
}


int main1() {
  int arr_loc[5] = {};
  int *parr = arr_loc;
  return *getarr1(parr);
}
