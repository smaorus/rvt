void *g;

void f() {
  *(int*)g = 1;
}

int main () {
  int a;
  g = &a;

  f();
  return a;
}
