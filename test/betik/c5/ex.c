void f(void *a) {
	*(int*)a = 9;
}

int main () {
  int a;
  f(&a);
  return a;
}
