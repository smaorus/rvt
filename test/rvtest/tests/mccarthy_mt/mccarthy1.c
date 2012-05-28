int f91(int x) {
	if (x < 101)
		return f91(f91(11 + x));
	return x - 10;
}

int main() {
	int i1;
	int res1 = f91(i1);
	return res1;
}
