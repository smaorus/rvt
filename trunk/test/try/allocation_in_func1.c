int ff(int **p) {
	int ret = **p;
	int t = 1;
	**p = t;
	return ret;
	}


int f(int x) {
	int **p,  *z1, z2, y, t = 1;
	z1 = &z2;	
	p = &z1;	
	**p = t;
	y = ff(p);
	return x + y + **p;
}


int main() {
	int xm;
	return f(xm);		
}

