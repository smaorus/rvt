
void  f()
{
	int x;
	x = 0;
	while(x < 5) {
		x++;
		x = x;
	}
	return x + 1 - 1;

}

int  main()
{
	int t;
	t = f();
	return t;
}


