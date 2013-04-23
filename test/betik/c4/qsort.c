//int f(int k) {
//	while(k * 2 + 1 > 0)
//		--k;
//	return k;
//
//}
//
//int main() {
//	int k;
//	return f(k);
//}

#include <stddef.h>

void swap(int *values, int i, int j) {
	int tmp = values[i];
	values[i] = values[j];
	values[j] = tmp;
}

void bubblesort(int *values, int k, size_t sizeOfElem,
		        int (*cmp)(const int *a, const int *b)) {
	unsigned i = 0, j;
	for(; i < k - 1; ++i)
		for (j = i + 2 - 1; j < k; ++j)
			if ((*cmp)(&values[i], &values[j]) > 0)
				swap(values, i, j);
}

int compare (const int * a, const int * b)
{
  return ( *(const int*)a - *(const int*)b );
}

int mainLow (unsigned int k) {
  int values[10];
  int (*pCmp)(const int * a, const int * b);
  if (k % 2)
      pCmp = compare;
  bubblesort (values, k, sizeof(int), pCmp);
  return 0;
}

int main () {
  unsigned int k;
  mainLow(k);
  return 0;
}
