/* type-specific outlined function created by prependOutlineFunction() */
unsigned int rv_mult_int__unsigned_int_(int x, unsigned int y);


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
void  assert(_Bool  c);
typedef struct {
  int  top;
  void  *buffer;
  unsigned int  item_length;
} stack_t;
stack_t  *create_stack(unsigned int  item_length);

int  main();

stack_t  *create_stack(unsigned int  item_length)
{
  ;
  stack_t  *s = (stack_t *) (malloc(sizeof(stack_t ) ));
  ;
  s->buffer = malloc(rv_mult_int__unsigned_int_(1024,item_length));
  s->top = 0;
  ;
  s->item_length = item_length;
  return s;
}


int  main()
{
  stack_t  *s = create_stack(10);

  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
