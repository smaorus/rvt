// Problem: the while loop reads g1.b but not g1.a. rvt marks g1 as a read (no distinction between the fields). 
// As a result, the UF that replaces the while (in f.rv.c), requires g1.a to be equal on both sides in order to return the same value.
// specifically, the line "equal = equal && (rvp_g1_3->a == rvp_g1->a);" in f.rv.c should be removed. 
// the generation of these lines is in RVGen::gen_struct_op


#include<stdlib.h>

struct stam {
	int a;
	int b;
};


int g;

int f(int x) {
	int i = 0;
	struct stam g1;
	g1.b = 1;
	while (i < x) {
		i++;
		g = g1.b;
		g1.a = 2;
	}
	return 0;
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
