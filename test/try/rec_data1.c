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
	*c = b.x + 2 - 1 - 1;
}

int main() {
	struct s *a, bs;
	int b[1];
	a = (struct s*)malloc(sizeof(struct s));
	f(a, b, bs);
}
