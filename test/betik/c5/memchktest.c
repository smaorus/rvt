#include<string.h>
#include<stdlib.h>
int main() {
       void *a, *b;
       a = (void *)malloc(sizeof(int));
       b = (void *)malloc(sizeof(int));
       *(int*)a = 0xFFFFFFFF;
       *(int*)b = 0xFFFFFFFF;
       assert(*(int*)a == 0xFFFFFFFF);
       assert(*(int*)b == 0xFFFFFFFF);
       assert(!memcmp(a,b,sizeof(int)));
       return memcmp(a,b,sizeof(int));
}
