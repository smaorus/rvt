/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "/cygdrive/c/gitrvt/rvtweb/samples/Basecase_not_in_sync/p2.c"
# 1 "<command-line>"
# 1 "/cygdrive/c/gitrvt/rvtweb/samples/Basecase_not_in_sync/p2.c"
int fact(int n){
   if (n <= 0) return 1;
   return n * fact(n-1);
}

int main(){
    int n;
    return fact(n);
}
