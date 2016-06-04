# 1 "./bug15.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./bug15.c"
int main(void) {
 int x = 1, y;
 while (x <= 9) {
  y = x + 2;
  x = 2 * y;
 }
 return x << 1;
}
