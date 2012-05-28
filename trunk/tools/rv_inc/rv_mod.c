/* predefined outlined function */
void __CPROVER_assume(_Bool);
int rv_mod (int x, int y) {__CPROVER_assume(y > 0); return x % y;}
