// This program shows the problem with unified unrolling depths of unbounded structures. 
// the loop cannot unroll at all, because before the loop we do not allocate a structure
// (we only allocate a pointer to the structure. But since the content can be 0, we cannot
// deref c. ) So we can only run it with no -dk flag (this will give us the default depth 0).
// but in order to check ff, the default 0 means it is not checked in this case. 
// The solution is to allow different depths to different functions. 


#include <stdlib.h>
struct stam_tag{
	int a;	
	struct stam_tag *c;
};


int ff(struct stam_tag *p) {
	p -> a = (p -> a) + 1;
}

int main() {
	struct stam_tag *l1, *l2;	
	int i;
	l2 = l1 = (struct stam_tag*)malloc(sizeof(struct stam_tag));
	for (i = 0; i < 4; ++i) {
		l1 -> a = i;
		l1 -> c = (struct stam_tag*)malloc(sizeof(struct stam_tag));
		l1 = l1 -> c;
		
	}
	
	ff(l2);	
//	l1 -> a = 2;
	return 0;
}
