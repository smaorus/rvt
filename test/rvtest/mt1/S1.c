/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 ".//try1_side1.c"
# 1 "<command-line>"
# 1 ".//try1_side1.c"
# 1 "try.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "try.c"


int n;

int ident(int n) {
 return n ;
}

int sum(int n) {
  n = ident(n + 1) - 1;

  if (n <= 1) return n;
  return n + sum(n-1);
}

int main() {
return sum(n);
}
