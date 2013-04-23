void f(void *a) {
	*(int*)a = 9;
}

int main () {
  int a;
  int *pA = &a;
  f(pA);
  return a;
}
