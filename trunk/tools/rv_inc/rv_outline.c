/* predefined outlined functions */
void __CPROVER_assume(_Bool);
float rv_mult(float x, float y) {return x * y;}
float rv_div (float x, float y) {__CPROVER_assume(y > 0); return x / y;}
int rv_mod (int x, int y) {__CPROVER_assume(y != 0); return x % y;}
