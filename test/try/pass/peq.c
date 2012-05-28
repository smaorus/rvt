# 1 "try.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "try.c"


int n;

int sum(int n) {
	 
		if (n <= 1) return n;
		return n + sum(n-1);
}

int main() {
return sum(n);
}
