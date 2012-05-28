// if we use the array code (#define ARRAY in rv_main.cpp), it exposes a bug that causes it to identify 
// p below as an array, which leads to all sorts of problems.
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
	p -> data = p -> data + 1;
	p -> next -> data = 0;
	while (t < 5) {
		t = t + **l;
		(**l) ++;
		p -> data = p -> data + 1;
	}
}


int  main()
{
	struct list * p;
	p = (struct list *)malloc(sizeof(struct list));
	p -> next = (struct list *)malloc(sizeof(struct list));;
	p -> data = 0;	
	*gl = 2;
	g(p);
	return 0;
}


