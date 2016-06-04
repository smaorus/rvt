#include<stdlib.h>

struct stam {
	int a;
	int b;
};

struct stam g1;
int g;

int f(int x) {
	int i = 0;
	g1.b = 1;
	while (i < x) {
		i++;
		g = g1.b;
		g1.a = 2;
	}
	return 0;
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
