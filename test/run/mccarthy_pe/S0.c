/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./mccarthy.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./mccarthy.c"
int f91(int a) {
 if (a > 100)
  return a - 10;
 return f91(f91(a + 11));
}

int main() {
 int i;
 int res = f91(i);
 return res;
}
