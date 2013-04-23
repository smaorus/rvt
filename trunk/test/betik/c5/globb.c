void *g;

void f() {
  *(int*)g = 2;
}

int main () {
  int a;
  g = &a;

  f();
  return a;
}
