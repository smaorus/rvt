#include "rv_declarations.h"

/*** global declarations side 0: ***/
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
struct rvs0___FILE {
  int  flags;
};
typedef struct rvs0___FILE  rvs0_FILE;
int  rvs0_fflush(rvs0_FILE  *stream);
extern rvs0_FILE  *rvs0_stdin;
extern rvs0_FILE  *rvs0_stdout;
extern rvs0_FILE  *rvs0_stderr;
int  rvs0___CPROVER_printf_0(char  *format);
int  rvs0___CPROVER_printf_1(char  *format, long  opt_arg_0);
int  rvs0_fprintf_0(rvs0_FILE  *stream, char  *format);
int  rvs0_sprintf_0(char  *str, char  *format);
int  rvs0_snprintf_0(char  *str, unsigned int  size, char  *format);
int  rvs0_vsprintf_0(char  *rv_arg_0, char  *rv_arg_1);
int  rvs0_vprintf_0(char  *rv_arg_2);
int  rvs0_vfprintf_0(rvs0_FILE  *rv_arg_3, char  *rv_arg_4);
int  rvs0_scanf_0(char  *format);
int  rvs0_fscanf_0(rvs0_FILE  *stream, char  *format);
int  rvs0_sscanf_0(char  *str, char  *format);
rvs0_size_t  rvs0_fread(void  *ptr, rvs0_size_t  size, rvs0_size_t  nmemb, rvs0_FILE  *stream);
rvs0_size_t  rvs0_fwrite(void  *ptr, rvs0_size_t  size, rvs0_size_t  nmemb, rvs0_FILE  *stream);
int  rvs0_fseek(rvs0_FILE  *stream, long  off, int  whence);
rvs0_FILE  *rvs0_fopen(char  *path, char  *mode);
rvs0_FILE  *rvs0_fdopen(int  fildes, char  *mode);
rvs0_FILE  *rvs0_freopen(char  *path, char  *mode, rvs0_FILE  *stream);
long  rvs0_ftell(rvs0_FILE  *rv_arg_5);
int  rvs0_fclose(rvs0_FILE  *stream);
int  rvs0_fgetc(rvs0_FILE  *stream);
char  *rvs0_fgets(char  *s, int  size, rvs0_FILE  *stream);
int  rvs0_getc(rvs0_FILE  *stream);
int  rvs0_getchar();
char  *rvs0_gets(char  *s);
int  rvs0_ungetc(int  c, rvs0_FILE  *stream);
int  rvs0_fputc(int  c, rvs0_FILE  *stream);
int  rvs0_fputs(char  *s, rvs0_FILE  *stream);
int  rvs0_putc(int  c, rvs0_FILE  *stream);
int  rvs0_remove(char  *rv_arg_6);
int  rvs0_link(char  *path1, char  *path2);
extern int  rvs0_putchar(int  c);
extern int  rvs0_puts(char  *s);
void  rvs0_perror(char  *s);
int  rvs0_F(int  n);
int  rvs0_M(int  n);
int  rvs0_F(int  n);
int  rvs0_M(int  n);
int  rvs0_main();
int  rvs0_F(int  n);
unsigned char  chk0_Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
unsigned char  rvs0_Loop_main_for2(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_20);

/*** global declarations side 1: ***/
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
struct rvs1___FILE {
  int  flags;
};
typedef struct rvs1___FILE  rvs1_FILE;
int  rvs1_fflush(rvs1_FILE  *stream);
extern rvs1_FILE  *rvs1_stdin;
extern rvs1_FILE  *rvs1_stdout;
extern rvs1_FILE  *rvs1_stderr;
int  rvs1___CPROVER_printf_0(char  *format);
int  rvs1___CPROVER_printf_1(char  *format, long  opt_arg_0);
int  rvs1_fprintf_0(rvs1_FILE  *stream, char  *format);
int  rvs1_sprintf_0(char  *str, char  *format);
int  rvs1_snprintf_0(char  *str, unsigned int  size, char  *format);
int  rvs1_vsprintf_0(char  *rv_arg_7, char  *rv_arg_8);
int  rvs1_vprintf_0(char  *rv_arg_9);
int  rvs1_vfprintf_0(rvs1_FILE  *rv_arg_10, char  *rv_arg_11);
int  rvs1_scanf_0(char  *format);
int  rvs1_fscanf_0(rvs1_FILE  *stream, char  *format);
int  rvs1_sscanf_0(char  *str, char  *format);
rvs1_size_t  rvs1_fread(void  *ptr, rvs1_size_t  size, rvs1_size_t  nmemb, rvs1_FILE  *stream);
rvs1_size_t  rvs1_fwrite(void  *ptr, rvs1_size_t  size, rvs1_size_t  nmemb, rvs1_FILE  *stream);
int  rvs1_fseek(rvs1_FILE  *stream, long  off, int  whence);
rvs1_FILE  *rvs1_fopen(char  *path, char  *mode);
rvs1_FILE  *rvs1_fdopen(int  fildes, char  *mode);
rvs1_FILE  *rvs1_freopen(char  *path, char  *mode, rvs1_FILE  *stream);
long  rvs1_ftell(rvs1_FILE  *rv_arg_12);
int  rvs1_fclose(rvs1_FILE  *stream);
int  rvs1_fgetc(rvs1_FILE  *stream);
char  *rvs1_fgets(char  *s, int  size, rvs1_FILE  *stream);
int  rvs1_getc(rvs1_FILE  *stream);
int  rvs1_getchar();
char  *rvs1_gets(char  *s);
int  rvs1_ungetc(int  c, rvs1_FILE  *stream);
int  rvs1_fputc(int  c, rvs1_FILE  *stream);
int  rvs1_fputs(char  *s, rvs1_FILE  *stream);
int  rvs1_putc(int  c, rvs1_FILE  *stream);
int  rvs1_remove(char  *rv_arg_13);
int  rvs1_link(char  *path1, char  *path2);
extern int  rvs1_putchar(int  c);
extern int  rvs1_puts(char  *s);
void  rvs1_perror(char  *s);
int  rvs1_F(int  n);
int  rvs1_M(int  n);
int  rvs1_G(int  n);
int  rvs1_F(int  n);
int  rvs1_plusone(int  n);
int  rvs1_M(int  n);
int  rvs1_G(int  n);
int  rvs1_main();
int  rvs1_F(int  n);
unsigned char  chk1_Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
unsigned char  rvs1_Loop_main_while2(int  i, int  *rvp_rvretval);
unsigned char  rvs1_Loop_main_for3(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_21);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
unsigned char  chk0_Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval)
{
  if (!(*rvp_i < 20))
    return 0;
  {
    rvs0___CPROVER_printf_1("%2d ",(long ) (rvs0_F(*rvp_i)));
    (*rvp_l)++;
    if (*rvp_i > 20)
    {
      *rvp_rvretval = 3;
      return 123;
    }

  }

  (*rvp_i)++;
  return 0;
}


/*** Functions side 1: ***/
unsigned char  chk1_Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval)
{
  if (!(*rvp_i < 20))
    return 0;
  {
    rvs1___CPROVER_printf_1("%2d ",(long ) (rvs1_F(*rvp_i)));
    (*rvp_l)++;
    if (*rvp_i > 28)
    {
      *rvp_rvretval = 12;
      return 123;
    }

  }

  (*rvp_i)++;
  return 0;
}


/* Implementations of the uninterpreted functions: */

  /* Declarations of the CBMC uninterpreted functions */
int  __CPROVER_uninterpreted_4_retval(int );

  /* CBMC-UF side 0: */ 
int  rvs0_F(int  n)
{
  int  retval;

  /* Declarations: */


  /* Each output is assigned a UF:*/
  retval= __CPROVER_uninterpreted_4_retval(n);

  return retval;
}


  /* CBMC-UF side 1: */ 
int  rvs1_F(int  n)
{
  int  retval;

  /* Declarations: */


  /* Each output is assigned a UF:*/
  retval= __CPROVER_uninterpreted_4_retval(n);

  return retval;
}


  /* Declarations of the CBMC uninterpreted functions */
char  __CPROVER_uninterpreted_5_format(char , long );
int  __CPROVER_uninterpreted_5_retval(char , long );

  /* CBMC-UF side 0: */ 
int  rvs0___CPROVER_printf_1(char  *format, long  opt_arg_0)
{
  int  retval;

  /* Declarations: */
  char  rv_D0_0;	/* Generated by:  gen_side0_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* Protecting pointers from being NULL-dereferenced: */
  if (format== 0) {
  format = &rv_D0_0;	/* Generated by:  gen_side0_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }

  /* Each output is assigned a UF:*/
  *format= __CPROVER_uninterpreted_5_format(*format, opt_arg_0);
  retval= __CPROVER_uninterpreted_5_retval(*format, opt_arg_0);

  return retval;
}


  /* CBMC-UF side 1: */ 
int  rvs1___CPROVER_printf_1(char  *format, long  opt_arg_0)
{
  int  retval;

  /* Declarations: */
  char  rv_D1_0;	/* Generated by:  gen_side1_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* Protecting pointers from being NULL-dereferenced: */
  if (format== 0) {
  format = &rv_D1_0;	/* Generated by:  gen_side1_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }

  /* Each output is assigned a UF:*/
  *format= __CPROVER_uninterpreted_5_format(*format, opt_arg_0);
  retval= __CPROVER_uninterpreted_5_retval(*format, opt_arg_0);

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
  int  *rvs0_rvp_l;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs1_rvp_l;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs0_rvp_rvretval;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  *rvs1_rvp_rvretval;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  rv_D2_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D3_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D4_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D5_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D6_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/
  int  rv_D7_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* output: */
  /* output: */
  /* output: */
  /* Allocations for side 0: */
  rvs0_rvp_i = &rv_D2_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs0_rvp_l = &rv_D3_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs0_rvp_rvretval = &rv_D4_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  /* Allocations for side 1: */
  rvs1_rvp_i = &rv_D5_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs1_rvp_l = &rv_D6_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  rvs1_rvp_rvretval = &rv_D7_0;	/* Generated by:  gen_arg_alloc_side(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/

  /* Assume input args are equal: */ 
  *rvs0_rvp_i = *rvs1_rvp_i;	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=4](613)(379)(293)/ rv_temps.cpp:362*/
  *rvs0_rvp_l = *rvs1_rvp_l;	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=4](613)(379)(293)(608)/ protect_pointer [op=4](613)(379)(293)/ rv_temps.cpp:362*/
  *rvs0_rvp_rvretval = *rvs1_rvp_rvretval;	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=4](613)(379)(293)(608)/ protect_pointer [op=4](613)(379)(293)(608)/ protect_pointer [op=4](613)(379)(293)/ rv_temps.cpp:362*/

  /* run each side's main() */
  retval0 = chk0_Loop_main_for1(rvs0_rvp_i, rvs0_rvp_l, rvs0_rvp_rvretval);
  retval1 = chk1_Loop_main_for1(rvs1_rvp_i, rvs1_rvp_l, rvs1_rvp_rvretval);
  /* Assertions: */

  /* Compare return values: */ 
  assert( retval0 == retval1 );	/* Generated by:  gen_main(608)(613)(379)(309)/ rv_temps.cpp:352*/

  /* Compare output args: */ 
  assert( *rvs0_rvp_i == *rvs1_rvp_i );	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=6](613)(379)(309)/ rv_temps.cpp:352*/
  assert( *rvs0_rvp_l == *rvs1_rvp_l );	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=6](613)(379)(309)(608)/ protect_pointer [op=6](613)(379)(309)/ rv_temps.cpp:352*/
  assert( *rvs0_rvp_rvretval == *rvs1_rvp_rvretval );	/* Generated by:  gen_args_equality(608)/ protect_pointer [op=6](613)(379)(309)(608)/ protect_pointer [op=6](613)(379)(309)(608)/ protect_pointer [op=6](613)(379)(309)/ rv_temps.cpp:352*/


  return 0;
}
