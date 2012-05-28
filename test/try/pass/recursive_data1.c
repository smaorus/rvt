#include <stdlib.h>
struct out {
	int z;
};

struct in {
	int y;
};

struct s { 
	int x;
	struct in inr;
	struct out *outr;
} ;


void f(struct s *a) {
	int t = 1;
	a -> x = 1 - t;
	a -> inr.y = 1 - t;
	a -> outr = (struct out*)malloc(sizeof(struct out));
	a -> outr -> z = 1 - t;
}

int main() {
	struct s a[1];
	f(a);
}
