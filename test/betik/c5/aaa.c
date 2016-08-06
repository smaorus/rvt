#include <memory.h>
//#include <assert.h>
//#include <stdio.h>


struct AAA {
  char f1, f2, f3, f4, f5;
};

int eq_aaa(void *a, void *b) {
  struct AAA *pA = (struct AAA*)a, *pB = (struct AAA*)b;
  int res = 0;
  if (pA->f1 != pB->f1) return 0;
  if (pA->f2 != pB->f2) return 0;
  if (pA->f3 != pB->f3) return 0;
  if (pA->f4 != pB->f4) return 0;
  if (pA->f5 != pB->f5) return 0;
  return 1;
}

int main() {
  struct AAA v1, v2;
  void *a = &v1;
  void *b = &v2;

  //*(struct AAA*)a = *(struct AAA*)b;

  //assert(eq_aaa(a, b));
  assert (*(struct AAA*)a == *(struct AAA*)b);
  //printf ("equal = %d\n", eq_aaa(a, b));
  return 0;
}
