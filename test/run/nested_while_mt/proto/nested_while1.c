#include<stdlib.h>
int g;
int f(int x) {
	int i = 0;
	while (i < x) {
		i = i + 1;
		g--;
		while(x < i) {
			x--;
			g = g + 1;
			return g;
		}
	}
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
