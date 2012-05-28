// currently doesn't work because of cbmc bug. Complains that **p inside ff is not allocated. Bug report sent 17/3/11.

int ff(int **p) {
	int ret = **p;
	**p = 1;
	return ret;
	}


int f(int x) {
	int **p, *z1, z2, y;	
	z1 = &z2;
	p = &z1;	
	**p = 1;
	y = ff(p);
	return x + y + **p;
}


int main() {
	int xm;
	return f(xm);		
}
