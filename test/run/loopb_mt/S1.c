/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./loopb1.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./loopb1.c"


typedef struct B {
  int a;
  struct B* next;
} B_t;


void g(B_t *pb, B_t* src, int c) {
  B_t *cur = src;
  pb->a = 0;

  while (cur->a != 0) {
    pb->a += 2;
    cur = cur->next;
  }
  pb->a += cur->a;
}



int main() {
        B_t b1,b2;
        g(&b1, &b2, b2.a);
        return 0;
}
