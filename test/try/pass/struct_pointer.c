// seems like a bug in cbmc. complains about allocation although the allocation is fine. 

#include<stdlib.h>

struct stam {
	int a;
	int *b;
};

struct stam g1;
int g;

int f(int x) {
	int i = 0;
	g1.b = (int *)malloc(sizeof(int));
	*g1.b = 1;
	while (i < x) {
		int t = 2;
		i++;
		g = *g1.b;
		g1.a = t;
	}
	return 0;
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
