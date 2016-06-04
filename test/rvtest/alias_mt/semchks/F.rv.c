#include "rv_declarations.h"

/*** global declarations of both sides: ***/
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

/*** global declarations side 0: ***/
typedef int  (*rvs0_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_0, void  *rv_arg_1);
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
void  rvs0_exit(int  status);
char  *rvs0_getenv(char  *name);
int  rvs0_system(char  *string);
void  rvs0_abort();
void  *calloc(size_t  nmemb, size_t  size);
void  *malloc(size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, size_t  size);
int  rvs0_atoi(char  *nptr);
long  rvs0_atol(char  *nptr);
long long  rvs0_atoll(char  *nptr);
long long  rvs0_atoq(char  *nptr);
float  rvs0_atof(char  *nptr);
int  rvs0_rand();
void  rvs0_srand(unsigned int  seed);
long  rvs0_random();
void  rvs0_srandom(unsigned int  seed);
char  *rvs0_initstate(unsigned int  seed, char  *state, size_t  n);
char  *rvs0_setstate(char  *state);
int  rvs0_mkstemp(char  *temp);
void  rvs0_qsort(void  *base, size_t  num, size_t  width, rvs0_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
int  chk0_F(int  *n);
int  rvs0_main();
void  __CPROVER_assume(_Bool  rv_arg_6);

/*** global declarations side 1: ***/
typedef int  (*rvs1_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_2, void  *rv_arg_3);
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
void  rvs1_exit(int  status);
char  *rvs1_getenv(char  *name);
int  rvs1_system(char  *string);
void  rvs1_abort();
void  *calloc(size_t  nmemb, size_t  size);
void  *malloc(size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, size_t  size);
int  rvs1_atoi(char  *nptr);
long  rvs1_atol(char  *nptr);
long long  rvs1_atoll(char  *nptr);
long long  rvs1_atoq(char  *nptr);
float  rvs1_atof(char  *nptr);
int  rvs1_rand();
void  rvs1_srand(unsigned int  seed);
long  rvs1_random();
void  rvs1_srandom(unsigned int  seed);
char  *rvs1_initstate(unsigned int  seed, char  *state, size_t  n);
char  *rvs1_setstate(char  *state);
int  rvs1_mkstemp(char  *temp);
void  rvs1_qsort(void  *base, size_t  num, size_t  width, rvs1_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
int  chk1_F(int  *n);
int  rvs1_main();
void  __CPROVER_assume(_Bool  rv_arg_7);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
int  chk0_F(int  *n)
{
  __CPROVER_assume(n != 0);
  int  *a;
  a = n;
  *a = 2;
  return 0;
}


/*** Functions side 1: ***/
int  chk1_F(int  *n)
{
  __CPROVER_assume(n != 0);
  if (*n <= 0)
  {
    return 1;
  }

  *n = *n - 1;
  return 0;
}

