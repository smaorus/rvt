
void mstrcpy(char *dst, char *src);
int  mprintf (const char *s1, char *s2);
void *malloc();

int main() {
	char *s;
	s = (char *)malloc(sizeof(char));
	mstrcpy(s, "aa1");
	mprintf("%s", s);

	return 0;
}
