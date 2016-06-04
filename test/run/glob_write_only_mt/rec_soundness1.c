
#include<stdlib.h>

int g;

int f(int x) {
	if (x < 5) return 0;
	g = 2 ;
	f(x-1);
	return 0;
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
