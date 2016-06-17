/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "/cygdrive/c/abs2.c"
# 1 "<command-line>"
# 1 "/cygdrive/c/abs2.c"

int r(int n){
 if (n < 0) return 8;
 return 5;
}

int f(int n){
 if (n <= 0) return 1;
 if (f(n-1) < 0) return 4;
 else return r(n);
}


int main(int x){

 return f(x);

}
