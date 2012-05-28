int M(int n);  


int F(int n){  
	if ( n == 0 ) return 1;  
	return n - M(F(n-1));
} 


int M(int n) {  
	if ( n == 0 ) return 0; 
	return n - F(M(n-1));
} 



int main(){  
	int i, l = 0;   

	for(i = 0; i < 20; i++) {    
		l += F(i);  		
	}

	for(i = 0; i < 20; i++) { 
		l +=  M(i);  		
	}  

	return l;
}