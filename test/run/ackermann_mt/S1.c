/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./ackermann1.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./ackermann1.c"
int A(int m, int n) {
 if (m > 0 && n == 0) return A(m - 1, 1);
 if (m == 0) return n + 1;
 return A(m - 1, A(m, n - 1));
}


main() {
        int x, y;
 return A(y, x);
}
