//  This example exposes a soundness rvt bug that occurs with recursive functions.
// Although the programs are different (the value of g at the exit from f is different), rvt reports them as equal. 
// The reason is that the UF that replaces the recursive call should accept as input  
// both the inputs and the outputs of the function. In this case g is not read and hence was not
// marked as an input, but it should be nevertheless. Note that this problem does not occur with loops
// since with loops we now don't call UFs.

#include<stdlib.h>

int g;

int f(int x) {
	if (x < 5) return 0;
	g = 1;
	f(x-1);
	return 0;
}

int main() {
	int xm;
	f(xm);	
	return 0;
}
