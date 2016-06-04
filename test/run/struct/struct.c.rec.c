

typedef int  (*rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_0, void  *rv_arg_1);
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
struct stam {
  int  a;
  int  b;
};
struct stam  g1;
int  g;
int  f(int  x);

int  main();

unsigned char  Loop_f_while1(int  x, int  *rvp_i, int  *rvp_rvretval);


int  f(int  x)
{
  int  rvretval = 0;
  int  i = 0;

  g1.b = 1;
  {
    Loop_f_while1(x,&i,&rvretval);
  }

  return 0;
}

unsigned char  Loop_f_while1(int  x, int  *rvp_i, int  *rvp_rvretval)
{
  if( !(*rvp_i < x) )
    return 0;

  {
    (*rvp_i)++;
    g = g1.b;
    g1.a = 2;
  }

  return 0;
}



int  main()
{
  int  xm;

  f(xm);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
