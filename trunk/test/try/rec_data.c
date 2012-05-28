#include <stdlib.h>
struct in {
	int y;
} v;

struct s { 
	int x;
	struct in inr;
} v1;


void f(struct s *a, int *c, struct s b) {
	a -> x = 0;
	*c = b.x;
}

int main() {
	struct s *a, bs;
	int c[1];
	a = (struct s*)malloc(sizeof(struct s));
	f(a, c, bs);
}
