#include "rv_declarations.h"

/*** global declarations side 0: ***/
typedef int  (*rvs0_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_0, void  *rv_arg_1);
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
typedef int  rvs0_pid_t;
typedef unsigned int  rvs0_size_t;
typedef unsigned char  rvs0_u_char;
typedef unsigned long  rvs0_ulong;
typedef unsigned short  rvs0_ushort;
typedef unsigned int  rvs0_uint;
typedef unsigned int  rvs0_off_t;
typedef unsigned int  rvs0_mode_t;
typedef unsigned int  rvs0_u_int;
typedef int  rvs0_uid_t;
void  rvs0_exit(int  status);
char  *rvs0_getenv(char  *name);
int  rvs0_system(char  *string);
void  rvs0_abort();
void  *calloc(rvs0_size_t  nmemb, rvs0_size_t  size);
void  *malloc(rvs0_size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, rvs0_size_t  size);
int  rvs0_atoi(char  *nptr);
long  rvs0_atol(char  *nptr);
long long  rvs0_atoll(char  *nptr);
long long  rvs0_atoq(char  *nptr);
float  rvs0_atof(char  *nptr);
int  rvs0_rand();
void  rvs0_srand(unsigned int  seed);
long  rvs0_random();
void  rvs0_srandom(unsigned int  seed);
char  *rvs0_initstate(unsigned int  seed, char  *state, rvs0_size_t  n);
char  *rvs0_setstate(char  *state);
int  rvs0_mkstemp(char  *temp);
void  rvs0_qsort(void  *base, rvs0_size_t  num, rvs0_size_t  width, rvs0_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
int  rvs0_g;
int  rvs0_f(int  x);
int  rvs0_main();
unsigned char  chk0_Loop_f_while1(int  *rvp_i, int  *rvp_x, int  *rvp_rvretval);
unsigned char  rvs0_Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval);
unsigned char  rvs0_Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_8);

/*** global declarations side 1: ***/
typedef int  (*rvs1_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_2, void  *rv_arg_3);
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
typedef int  rvs1_pid_t;
typedef unsigned int  rvs1_size_t;
typedef unsigned char  rvs1_u_char;
typedef unsigned long  rvs1_ulong;
typedef unsigned short  rvs1_ushort;
typedef unsigned int  rvs1_uint;
typedef unsigned int  rvs1_off_t;
typedef unsigned int  rvs1_mode_t;
typedef unsigned int  rvs1_u_int;
typedef int  rvs1_uid_t;
void  rvs1_exit(int  status);
char  *rvs1_getenv(char  *name);
int  rvs1_system(char  *string);
void  rvs1_abort();
void  *calloc(rvs1_size_t  nmemb, rvs1_size_t  size);
void  *malloc(rvs1_size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, rvs1_size_t  size);
int  rvs1_atoi(char  *nptr);
long  rvs1_atol(char  *nptr);
long long  rvs1_atoll(char  *nptr);
long long  rvs1_atoq(char  *nptr);
float  rvs1_atof(char  *nptr);
int  rvs1_rand();
void  rvs1_srand(unsigned int  seed);
long  rvs1_random();
void  rvs1_srandom(unsigned int  seed);
char  *rvs1_initstate(unsigned int  seed, char  *state, rvs1_size_t  n);
char  *rvs1_setstate(char  *state);
int  rvs1_mkstemp(char  *temp);
void  rvs1_qsort(void  *base, rvs1_size_t  num, rvs1_size_t  width, rvs1_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
int  rvs1_g;
int  rvs1_f(int  x);
int  rvs1_main();
unsigned char  chk1_Loop_f_while1(int  *rvp_i, int  *rvp_x, int  *rvp_rvretval);
unsigned char  rvs1_Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval);
unsigned char  rvs1_Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_9);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
unsigned char  chk0_Loop_f_while1(int  *rvp_i, int  *rvp_x, int  *rvp_rvretval)
{
  if (!(*rvp_i < *rvp_x))
    return 0;
  {
    (*rvp_i)++;
    rvs0_g--;
    {
      unsigned char  rv_ltc_val;

      switch (rv_ltc_val = rvs0_Loop_f_while1_while1(*rvp_i,rvp_x,rvp_rvretval))
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


/*** Functions side 1: ***/
unsigned char  chk1_Loop_f_while1(int  *rvp_i, int  *rvp_x, int  *rvp_rvretval)
{
  if (!(*rvp_i < *rvp_x))
    return 0;
  {
    *rvp_i = *rvp_i + 1;
    rvs1_g--;
    {
      unsigned char  rv_ltc_val;

      switch (rv_ltc_val = rvs1_Loop_f_while1_while1(*rvp_i,rvp_x,rvp_rvretval))
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


/* Implementations of the uninterpreted functions: */

  /* Declarations of the CBMC uninterpreted functions */
int  __CPROVER_uninterpreted_rvp_x(int , int , int , int );
int  __CPROVER_uninterpreted_rvp_rvretval(int , int , int , int );
int  __CPROVER_uninterpreted_rvs0_g(int , int , int , int );
unsigned char  __CPROVER_uninterpreted_retval(int , int , int , int );

  /* CBMC-UF side 0: */ 
unsigned char  rvs0_Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval)
{
  unsigned char  retval;

  /* Declarations: */
  int  rv_D4_0;	/* Generated by:  gen_side0_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D5_0;	/* Generated by:  gen_side0_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* Protecting pointers from being NULL-dereferenced: */
  if (rvp_x== 0) {
  rvp_x = &rv_D4_0;	/* Generated by:  gen_side0_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }
  if (rvp_rvretval== 0) {
  rvp_rvretval = &rv_D5_0;	/* Generated by:  gen_side0_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }

  /* Each output is assigned a UF:*/
  *rvp_x= __CPROVER_uninterpreted_rvp_x(i, *rvp_x, *rvp_rvretval, rvs0_g);
  *rvp_rvretval= __CPROVER_uninterpreted_rvp_rvretval(i, *rvp_x, *rvp_rvretval, rvs0_g);
  rvs0_g= __CPROVER_uninterpreted_rvs0_g(i, *rvp_x, *rvp_rvretval, rvs0_g);
  retval= __CPROVER_uninterpreted_retval(i, *rvp_x, *rvp_rvretval, rvs0_g);

  return retval;
}


  /* CBMC-UF side 1: */ 
unsigned char  rvs1_Loop_f_while1_while1(int  i, int  *rvp_x, int  *rvp_rvretval)
{
  unsigned char  retval;

  /* Declarations: */
  int  rv_D6_0;	/* Generated by:  gen_side1_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D7_0;	/* Generated by:  gen_side1_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* Protecting pointers from being NULL-dereferenced: */
  if (rvp_x== 0) {
  rvp_x = &rv_D6_0;	/* Generated by:  gen_side1_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }
  if (rvp_rvretval== 0) {
  rvp_rvretval = &rv_D7_0;	/* Generated by:  gen_side1_cbmc_uf(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }

  /* Each output is assigned a UF:*/
  *rvp_x= __CPROVER_uninterpreted_rvp_x(i, *rvp_x, *rvp_rvretval, rvs1_g);
  *rvp_rvretval= __CPROVER_uninterpreted_rvp_rvretval(i, *rvp_x, *rvp_rvretval, rvs1_g);
  rvs1_g= __CPROVER_uninterpreted_rvs0_g(i, *rvp_x, *rvp_rvretval, rvs1_g);
  retval= __CPROVER_uninterpreted_retval(i, *rvp_x, *rvp_rvretval, rvs1_g);

  return retval;
}

  /* now starting main */

int main()
{
  _Bool equal = 1;
  /* Declarations: */
  unsigned char  retval0;	/* Generated by:  gen_retval_declarations/ rv_temps.cpp:269*/
  unsigned char  retval1;	/* Generated by:  gen_retval_declarations/ rv_temps.cpp:269*/
  int  *rvs0_rvp_i;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs1_rvp_i;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs0_rvp_x;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs1_rvp_x;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs0_rvp_rvretval;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs1_rvp_rvretval;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  rv_D8_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D9_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D10_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D11_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D12_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D13_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* output: */
  /* output: */
  /* output: */
  /* Allocations for side 0: */
  rvs0_rvp_i = &rv_D8_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs0_rvp_x = &rv_D9_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs0_rvp_rvretval = &rv_D10_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  /* Allocations for side 1: */
  rvs1_rvp_i = &rv_D11_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs1_rvp_x = &rv_D12_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs1_rvp_rvretval = &rv_D13_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/

  /* Assume input args are equal: */ 
  *rvs0_rvp_i = *rvs1_rvp_i;	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=4](613)(379)(293)/ rv_temps.cpp:362*/
  *rvs0_rvp_x = *rvs1_rvp_x;	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=4](613)(379)(293)(608)/ protect_pointer [op=4](613)(379)(293)/ rv_temps.cpp:362*/
  *rvs0_rvp_rvretval = *rvs1_rvp_rvretval;	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=4](613)(379)(293)(608)/ protect_pointer [op=4](613)(379)(293)(608)/ protect_pointer [op=4](613)(379)(293)/ rv_temps.cpp:362*/

  /* Begin: Assume globals are equal: */ 
//nondet values for side 0:
  rvs0_g = (int )nondet_long();	/* Generated by:  gen_equal_nondet_globals(608)(613)(379)(249)/ rv_temps.cpp:383*/
//alloc for side 1:
//copy leaves from side 0 to 1:
  rvs1_g = rvs0_g;	/* Generated by:  gen_equal_nondet_globals(608)(613)(379)(249)(601)(608)(613)(379)(284)/ rv_temps.cpp:362*/
//until here

  /* End: Assume globals are equal: */ 
// for asserting global equality:

  /* run each side's main() */
  retval0 = chk0_Loop_f_while1(rvs0_rvp_i, rvs0_rvp_x, rvs0_rvp_rvretval);
  retval1 = chk1_Loop_f_while1(rvs1_rvp_i, rvs1_rvp_x, rvs1_rvp_rvretval);
  /* Assertions: */

  /* Compare return values: */ 
  assert( retval0 == retval1 );	/* Generated by:  gen_main(608)(613)(379)(309)/ rv_temps.cpp:352*/

  /* Compare output args: */ 
  assert( *rvs0_rvp_i == *rvs1_rvp_i );	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=6](613)(379)(309)/ rv_temps.cpp:352*/
  assert( *rvs0_rvp_x == *rvs1_rvp_x );	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=6](613)(379)(309)(608)/ protect_pointer [op=6](613)(379)(309)/ rv_temps.cpp:352*/
  assert( *rvs0_rvp_rvretval == *rvs1_rvp_rvretval );	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=6](613)(379)(309)(608)/ protect_pointer [op=6](613)(379)(309)(608)/ protect_pointer [op=6](613)(379)(309)/ rv_temps.cpp:352*/
  assert( rvs0_g == rvs1_g );	/* Generated by:  gen_globals_check_output(608)(613)(379)(309)/ rv_temps.cpp:352*/


  return 0;
}
