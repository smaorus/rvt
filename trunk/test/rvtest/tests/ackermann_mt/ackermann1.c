int A(int m, int n) {
	if (m > 0 && n == 0) return A(m - 1, 1);
	if (m == 0) return n + 1;
	return A(m - 1, A(m, n - 1));
}


main() {
        int x, y;
	return A(y, x);
}
