// cbmc complains about allocation in line 25, although the malloc is right above it.
// if we replace malloc with allocation in main with an address of another variable, it also 
// complains without justification.

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
	a -> x = 0;
	a -> inr.y = 0;
	//a -> outr = (struct out*)malloc(sizeof(struct out));
	a -> outr -> z = 0;	
}

int main() {
	struct s a[1];
	f(a);
}
