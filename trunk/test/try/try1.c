struct list {
	struct list *next;
	int num;
} *listvar;


void f() {
int t = 1;
	listvar = (void *)0;	
	listvar = listvar;
}

int main() {
	f();
	return 0;
}