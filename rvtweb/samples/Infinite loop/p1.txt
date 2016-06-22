void body(int *pX, int *pY) {
	if (*pX > *pY) {
		--*pX;
		++*pY;
	} else {
		++*pX;
		--*pY;
	}
}

int infiniteLoop(int x, int y) {
	while (x > 0 && y > 0)
		body(&x, &y);
	return x;
}

int main() {
	int i, j, res;
	res = infiniteLoop(i, j);
	return res;
}
