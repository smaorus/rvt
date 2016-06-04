/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./bugb.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./bugb.c"
enum Elem { ELEM0, ELEM1, ELEM2};

typedef struct B {
  int a;
  char b;
  enum Elem c;
  struct B* next;
} B_t;


int getA(B_t *src) {
 B_t tmp = {0, '\0', ELEM0, 0};
 if (src != 0)
  return src->a;

 return getA(&tmp);
}

void g(B_t *pb, B_t* src, enum Elem c) {
  B_t *cur = src;
  if (pb == 0 || src == 0)
    return;

  pb->a = getA(0);
  while (cur->next != 0)
    pb->b = 0;

  pb->b = cur->b;
}



int main() {
        B_t b1,b2;
        g(&b1, &b2, b2.c);

        return 0;
}
