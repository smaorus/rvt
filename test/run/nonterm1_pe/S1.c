/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./nonterm1.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./nonterm1.c"
int infiniteLoop(int x, int y) {
 while (x > 0 && y > 0)
  if (y < x) {
   x = x - 1;
   y = 1 + y;
  } else {
   y = y - 1;
   x = -~x;
  }
 return x;
}

int main() {
 int a, b, res;
 res = infiniteLoop(a, b);
 return res;
}
