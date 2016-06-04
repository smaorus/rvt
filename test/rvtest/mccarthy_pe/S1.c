/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 ".//mccarthy1.c"
# 1 "<command-line>"
# 1 ".//mccarthy1.c"
int f91(int x) {
 if (x < 101)
  return f91(f91(11 + x));
 return x - 10;
}

int main() {
 int i1;
 int res1 = f91(i1);
 return res1;
}
