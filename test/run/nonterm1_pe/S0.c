/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./nonterm.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./nonterm.c"
void body(int *pX, int *pY) {
 if (*pX > *pY) {
  --*pX;
  ++*pY;
 } else {
  ++*pX;
  --*pY;
 }
}

int infiniteLoop(int x, int y) {
 while (x > 0 && y > 0)
  body(&x, &y);
 return x;
}

int main() {
 int i, j, res;
 res = infiniteLoop(i, j);
 return res;
}
