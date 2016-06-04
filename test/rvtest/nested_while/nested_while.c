#include<stdlib.h>
int g;
int f(int x) {
	int i = 0;
	while (i < x) {
		i++;
		g--;
		while(x < i) {
			x--;
			g++;			
			return g;
		}
	}
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
