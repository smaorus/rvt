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
	l1 = (struct stam_tag*)malloc(sizeof(struct stam_tag));
	l2 = l1;
	for (i = 0; i < 4; ++i) {
		l1 -> a = i - 1;
		l1 -> c = (struct stam_tag*)malloc(sizeof(struct stam_tag));
		l1 = l1 -> c;
	}
	
	ff(l2);	
//	l1 -> a = 2;
	return 0;
}
