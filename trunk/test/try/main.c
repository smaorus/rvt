// main is compared for the value of its globals, as any other function.
// but main should only be checked for return value.  

int x;	
int f (int a) {	
	return a;
}

int main() {	
	x = f(1);
	return 0;
}
