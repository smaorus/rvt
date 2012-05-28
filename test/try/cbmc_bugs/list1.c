
#include <stdlib.h>
int *gl;
struct list{
	int data;
	struct list *next;
};


void g(struct list * p) {
	int t = *gl, *t1, t2, **l;
	t1 = &t2; 	
	l = &t1;
	t2 = 1;	
	t = 1;
	p -> data = p -> data + t;
	p -> next -> data = 0;
	while (t < 5) {
		t = t + **l;
		//t += 2 * (*l);
		(**l)++;
		p -> data = p -> data + 1;
	}
}


int  main()
{
	struct list * p;
	p = (struct list *)malloc(sizeof(struct list));
	p -> next = (struct list *)malloc(sizeof(struct list));;
	p -> data = 0;	
	g(p);
	return 0;
}


