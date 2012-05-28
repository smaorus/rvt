int a[5];
int test(int i) {
	int t = 1;
	return a[i] - t + 1;
}


int main() {
	int *p;
	
	int res,i = 2;
	res = test(i);
}