int infiniteLoop(int x, int y) {
	while (x > 0 && y > 0)
		if (y < x) {
			x = x - 1;
			y = 1 + y;
		} else {
			y = y - 1;
			x = -~x;
		}
	return x;
}

int main() {
	int a, b, res;
	res = infiniteLoop(a, b);
	return res;
}
