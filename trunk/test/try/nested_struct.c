
/* 
conclusions: 
1. fails due to cbmc bug: complains about dereference although it is fine.

2. check: When there are #include statements in the original code - they do not move to the target, 
which is a problem. (e.g. #include <stdio.h> in the source does not move to the semchcks. Then 
cbmc does not include the necessary definitions. 

*/
#include <stdlib.h>

struct in{
	int indata;
	struct in *innext;
};


//struct mylist{
//	int data;
//	struct in *to;
//	struct mylist *next;
//};
//typedef struct mylist *List;


void g(struct in * p) {
	int t = 1;
	p -> indata = t;
	p -> innext -> indata = 0;
}


int  main()
{
	struct in *l;
	
	l = (struct in *)malloc(sizeof(struct in));
	l -> innext = (struct in *)malloc(sizeof(struct in));	
	l -> indata = 0;
	l -> innext -> indata = 1;
	g(l);
	return 0;
}


