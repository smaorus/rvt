# 1 "try.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "try.c"


int n;

int ident(int n) {
int j, i = 0;

for (j = 0; j < n -  i; j++) ;
	return j  ;
}


int sum(int n) {
	 n = ident(n);
		if (n <= 1) return n;
		return n + sum(n-1);
}

int main() {
return sum(n);
}
