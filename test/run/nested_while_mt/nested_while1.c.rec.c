

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
int  g;
int  f(int  x);

int  main();

unsigned char  Loop_f_while1(int  *rvp_i, int  *rvp_x, int  *rvp_rvretval);

unsigned char  Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval);


int  f(int  x)
{
  int  rvretval = 0;
  int  i = 0;

  {
    switch (Loop_f_while1(&i,&x,&rvretval))
    {
    case 123:
      return rvretval;
    case 0:
      break;
    }

  }

}

unsigned char  Loop_f_while1(int  *rvp_i, int  *rvp_x, int  *rvp_rvretval)
{
  if( !(*rvp_i < *rvp_x) )
    return 0;

  {
    *rvp_i = *rvp_i + 1;
    g--;
    {
      unsigned char  rv_ltc_val;

      switch (rv_ltc_val = Loop_f_while1_while1(*rvp_i,rvp_x,rvp_rvretval))
      {
      case 123:
        return 123;
      default:
        return rv_ltc_val;
      case 0:
        break;
      }

    }

  }

  return 0;
}

unsigned char  Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval)
{
  if( !(*rvp_x < i) )
    return 0;

  {
    (*rvp_x)--;
    g = g + 1;
    {
      *rvp_rvretval = g;
      return 123;
    }

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
