int *g;

void f() {
  *g = 1;
}

int main () {
  int a;
  g = &a;

  f();
  return a;
}
