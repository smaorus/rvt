// assertion failure because of the two lines a = n; *a = 2; 
// The assertion failure only happens when we are aliased to a function argument. 
// seems to be related to the way this case is handled in RVCollect::process_binary


#include <stdlib.h>


int F(int *n){  
	int *a; 
	//int *g;   
	//a = g;
	a = n; 
	*a = 2; 
	return 0; 
} 

int main(){  
	int i, out = 0;   
	int *p = (int *)malloc(sizeof(int));
	
	*p = 10;
	out = F(p);
	return out;
}
