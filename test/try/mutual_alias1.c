#include <stdlib.h>
void myempty(){}
int F(int *n);
int M(int n); 


int F(int *n){  
	int *p = (int *)malloc(sizeof(int));
	int *a;
	a = n;
	*p = *a - 1;
	if ( *n <= 0 ) return 1; 
	if (*n == 1) return F(p);
	return *a - M(*n);
} 

int G(int n) {
	int *p = (int *)malloc(sizeof(int));
	int  t0, *t1, **a; 
	//a = (int **) (malloc(sizeof(int *) ));  doesn't work due to cbmc bug
	t1 = &t0;
	a = &t1;
	*a = p;
	*p = n - 1;
	return F(*a);
}


void plusone(int *n) {
	*n = *n + 1;
}

int M(int n) {  
	if ( n < 2 ) return 1; 	
	plusone(&n);
	return  n - 1 - G(n - 1);
} 

void H(int i) {
}

int main(){  
	int i, out = 0;   
	int *p = (int *)malloc(sizeof(int));
	for(i=0; i < 20; i++) {    
		*p = i;
		out += F(p);  		
	}  
	
	for(i=0; i < 20; i++) { 
		//out += M(i);  				
		H(M(i));
		myempty();
		}  
	return out;
}