#include <stdlib.h>

int *arr;

int f() {
  arr[1] = 8;
  return *arr;
}

int main() {
  unsigned x = sizeof(int) * 5;
  arr = (int*) malloc(x);
  f();
  return 0;
}
