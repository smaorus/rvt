//enum Elem { ELEM0, ELEM1, ELEM2};

typedef struct B {
  int a;
  struct B* next; 
} B_t;


void g(B_t *pb, B_t* src, int c) {
  B_t *cur = src;
  pb->a = 0;
  
  while (cur->a != 0) {
    pb->a += 1;
    cur = cur->next;    
  }
  pb->a += cur->a;
}


  
int main() {
        B_t b1,b2;
        g(&b1, &b2, b2.a);  
        return 0;
}
