int arr[5];
int *ptr;


int* getarr(int *a) {
  int *const loc_ptr = a;
  return ptr;
}


int main() {
  int arr_loc[5];
  int *parr = arr_loc;
  int res = *getarr(parr);
  return res;
}
