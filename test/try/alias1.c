#include <stdlib.h>


int F(int *n){	
	if ( *n <= 0 ) return 1; 
	*n = *n - 1;
	return 0;
} 

int main(){  
	int i, out = 0;   
	int *p = (int *)malloc(sizeof(int));
	*p = 10;
	out = F(p);
	*p = 2;
	return out;
}
