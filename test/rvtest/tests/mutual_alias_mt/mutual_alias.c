#include <stdlib.h>
void myempty(){}
int F(int *n);
int M(int n); 


int F(int *n){  
	int *p = (int *)malloc(sizeof(int));
	*p = *n - 1;
	if ( *n <= 0 ) return 1; 
	if (*n == 1) return F(p);
	return *n - M(*n);
} 

int G(int n) {
	int *p = (int *)malloc(sizeof(int));
	*p = n - 1;
	return F(p);
}

int M(int n) {  
	if ( n < 2 ) return 1; 	
	return n - G(n);
} 

//void H(int i) {
//}

int main(){  
	int i, out = 0;   
	int *p = (int *)malloc(sizeof(int));
	for(i=0; i < 20; i++) {    
		*p = i;
		out += F(p);  		
	}  
	
	for(i=0; i < 20; i++) { 
		//out += M(i);  				
		//H(M(i);
		myempty();
		}  
	return out;
}