
#include "rv_inputs.h"
void __CPROVER_assume(_Bool);
void assert(_Bool);

//int init_array(int n);
void bubble_sort(int *a, int sz);

//int n;
int a[5];

void bubble_sort(int *a, int sz)
{
    int i, j,t ;
    for (i=sz-1;i>0;i--) {
        for (j=0;j<i;j++) {
			__CPROVER_assume(j < 4 && j >= 0);
            if (a[j] < a[j+1]) {
                t = a[j];

                a[j] = a[j+1];
                a[j+1] = t;
                a[j] = a[j];
            }
        }
    }
}

int init_array(int n) {
    int j = 5;

    a[0] = 17;
    a[1] = 9;
    a[2] = 7;
    a[3] = 11;
    a[4] = 16;

    j = 17;

    return 0;
}



int main() {
 int i,
	 cmp;
 //__CPROVER_assume(n < 5);
 i = init_array(5);
 bubble_sort(a,5);
 cmp = a[0];

 return 0;

}
