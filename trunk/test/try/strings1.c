//#include<stdlib.h>
//#include <string.h>
char *strcpy(char *dest, const char *src);
int __CPROVER_printf(char *format, ...);
//int my(const char *format, char *s) {}

#define printf __CPROVER_printf

int main() {
	char s[4];
	//s = (char *)malloc(sizeof(char));
	strcpy(s, "aa1");
	printf("%s", s);
	//my("%s", s);

	return 0;
}
