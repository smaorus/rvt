

typedef int  (*rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_2, void  *rv_arg_3);
float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
typedef int  pid_t;
typedef unsigned int  size_t;
typedef unsigned char  u_char;
typedef unsigned long  ulong;
typedef unsigned short  ushort;
typedef unsigned int  uint;
typedef unsigned int  off_t;
typedef unsigned int  mode_t;
typedef unsigned int  u_int;
typedef int  uid_t;
void  exit(int  status);
char  *getenv(char  *name);
int  system(char  *string);
void  abort();
void  *calloc(size_t  nmemb, size_t  size);
void  *malloc(size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, size_t  size);
int  atoi(char  *nptr);
long  atol(char  *nptr);
long long  atoll(char  *nptr);
long long  atoq(char  *nptr);
float  atof(char  *nptr);
int  rand();
void  srand(unsigned int  seed);
long  random();
void  srandom(unsigned int  seed);
char  *initstate(unsigned int  seed, char  *state, size_t  n);
char  *setstate(char  *state);
int  mkstemp(char  *temp);
void  qsort(void  *base, size_t  num, size_t  width, rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
int  F(int  *n);

int  main();

int  F(int  *n)
{
  if (*n <= 0)
    return 1;
  *n = *n - 1;
  return 0;
}


int  main()
{
  int  i;
  int  out = 0;
  int  *p = (int *) (malloc(sizeof(int ) ));

  *p = 10;
  out = F(p);
  *p = 2;
  return out;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
