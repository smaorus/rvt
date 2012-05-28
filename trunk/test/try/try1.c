enum Elem { ELEM0, ELEM1, ELEM2};

typedef struct B {
  int a;
  enum Elem b;
 
} B_t;


void g(B_t *pb, B_t* src, enum Elem c) {
  B_t *cur = src;
  pb->a = 1;
  
  while (cur->a != 0) {
    pb->a += 2;
	//cur = cur->next;    
  }
  pb->a += cur->a;
}


  
int main() {
        B_t b1,b2;
		b2.b = 0;
        g(&b1, &b2, b2.b);  
        return 0;
}
