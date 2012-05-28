int M(int n); int plusone(int n); int G(int n); 


int F(int n){  
	int t = 1;
	if ( n == 0 ) return t;  
	return n - M(F(n-1));
} 

int M(int n) {  
	if ( n == 0 ) return 0; 
	return plusone(n) - 1 - G(M(n-1));
} 

/*******************************************/

int plusone(int n) {
	
	return n + 1;
}

int G(int n) {
	return F(n);
}

/*******************************************/

int main(){  
	int i, l = 0;

	for(i = 0; i < 20; i++) {    
		l += F(i);  		
	}
	
	for(i=0; i < 20; i++) { 
		l += M(i);  		
	}

	return l;
}