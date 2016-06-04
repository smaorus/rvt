/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 ".//simple_goto_elimination1.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 ".//simple_goto_elimination1.c"
int main() {
 int i = 0;

 label:
 i++;
 if (i == 9){
  return 1;
 }
 if (i > 0){
  goto label;
 }
 return 2;
}
