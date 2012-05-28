/* predefined outlined function */
void __CPROVER_assume(_Bool);
float rv_div (float x, float y) {__CPROVER_assume(y != 0); return x / y;}

