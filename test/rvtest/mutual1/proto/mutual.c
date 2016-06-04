#include <stdio.h> /* let us declare our functions; indeed here we need   really only M declaration, so that F can "see" it   and the compiler won't complain with a warning */

int F(int n);
int M(int n); 
int F(int n){  
	if ( n==0 ) return 1;  
	return n - M(F(n-1));
} 

int M(int n) {  
	if ( n == 0 ) return 0; 
	return n - F(M(n-1));
} 

int main(){  
	int i, l = 0;   
	for(i=0; i < 20; i++) {    
		printf("%2d ", F(i));  
		l++;
		if (i > 20) return 3;
	}  
	printf("\n");  
	for(i=0; i < 20; i++) { 
		printf("%2d ", M(i));  
		l++;
	}  
	printf("\n");  
	return l;
}
