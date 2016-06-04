int f91(int a) {
	if (a > 100)
		return a - 10;
	return f91(f91(a + 11));
}

int main() {
	int i;
	int res = f91(i);
	return res;
}
