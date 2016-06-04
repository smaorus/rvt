# 1 ".//collatz1.c"
# 1 "<command-line>"
# 1 ".//collatz1.c"
int f(int x) {
 int n;
 if (x <= 1) return x;
 n = x >> 1;
 if (x % 2)
  n = 6 * n + 4;
 return f(n);
}

int main() {
 int i, result;
 result = f(i);
}
