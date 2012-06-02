struct list {
	struct list *next;
	int num;
} *listvar;


void f() {
	listvar = (void *)0;	
}

int main() {
	f();
	return 0;
}