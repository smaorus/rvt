int main (void) {
	int y, x = 1;
	while (x < 10) {
		y = 2 + x;
		x = y + y;
	}
	return x*2;
}
