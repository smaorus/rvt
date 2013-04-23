int arr[5];
int *ptr;


int* getarr(int* a) {
  int *loc_ptr;
  loc_ptr = a;
  return ptr;
}


int main() {
  int arr_loc[5];
  int *parr = arr_loc;
  return *getarr(parr);
}
