int *g;

void f() {
  *g = 2;
}

int main () {
  int a;
  g = &a;

  f();
  return a;
}
