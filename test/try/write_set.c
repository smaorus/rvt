// main on both sides are not mapped to one another. The reason is that 
// in write_set1.c the structure 'my' is not marked as an output of main, 
// apparently because it is inside an expression.


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
	x = f(my);

	return 0;
}
