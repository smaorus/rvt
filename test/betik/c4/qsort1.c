int f(int k) {
	while(k + k + 1 > 0)
		--k;
	return k;
}

int main() {
	int k;
	return f(k);
}

//#include <stddef.h>
//
//int sign(int v) {
//  return v > 0 ? 1 : (v < 0 ? -1 : 0);
//}
//
//int compare (const int * a, const int * b) {
//  return sign( *(const int*)a - *(const int*)b );
//}
//
//void swap(int *values, int i, int j) {
//	int tmp = values[i];
//	values[i] = values[j];
//	values[j] = tmp;
//}
//
//void bubblesort(int *values, int k, size_t sizeOfElem,
//		        int (*cmp)(const int *a, const int *b)) {
//	unsigned i = 0, j;
//	for(; i < k - 1; ++i)
//		for (j = i + 1; j < k; ++j)
//			if ((*cmp)(&values[i], &values[j]) > 0)
//				swap(values, i, j);
//}
//
//int mainLow (unsigned int k) {
//  int values[10];
//  int (*pCmp)(const int * a, const int * b);
//  if (k & 1)
//      bubblesort (values, k, sizeof(int), compare);
//  else
//      bubblesort (values, k, sizeof(int), pCmp);
//  return 0;
//}
//
//int main () {
//  unsigned int k;
//  mainLow(k);
//}
