
typedef struct t {
	int data;
	struct t* next;
} st;

st *my;


int f (st *s) {
	int x = 1;
	 s -> data = x;
	return 0;
}


int main() {
	int x;
	x = f(my) + 1;
	x--;

	return 0;
}
