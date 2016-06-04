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
int  chk0_M(int  n);
int  rvs0_F(int  n);
int  chk0_M(int  n);
int  rvs0_main();
int  rvs0_F(int  n);
int  rvs0_M(int  n);
unsigned char  rvs0_Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
unsigned char  rvs0_Loop_main_for2(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_16);

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
int  chk1_M(int  n);
int  rvs1_G(int  n);
int  rvs1_F(int  n);
int  rvs1_plusone(int  n);
int  chk1_M(int  n);
int  rvs1_G(int  n);
int  rvs1_main();
int  rvs1_F(int  n);
int  rvs1_M(int  n);
unsigned char  rvs1_Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
unsigned char  rvs1_Loop_main_while2(int  i, int  *rvp_rvretval);
unsigned char  rvs1_Loop_main_for3(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_17);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
int  rvs0_M(int  n);
int  chk0_M(int  n)
{
  if (n == 0)
    return 0;
  return n - rvs0_F(rvs0_M(n - 1));
}


/*** Functions side 1: ***/
int  rvs1_plusone(int  n)
{
  return n + 1;
}

int  rvs1_M(int  n);
int  chk1_M(int  n)
{
  if (n == 0)
    return 0;
  return rvs1_plusone(n) - 1 - rvs1_G(rvs1_M(n - 1));
}

int  rvs1_G(int  n)
{
  return rvs1_F(n);
}


/* Implementations of the uninterpreted functions: */

typedef struct rv_UF_F_struct_tag {
  int  in_n;	/* Generated by:  gen_uf_item_decl(111)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  out_retval;	/* Generated by:  gen_uf_array(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  _Bool reach_equiv_flag;
} rv_UF_F_struct;
#define rv_UF_K_F 1 /* determined by RVT */
rv_UF_F_struct rv_UF_F_array[rv_UF_K_F];
int rv_UF_F_count[2] = {0,0};


 /*** uninterpreted function side 0: ***/ 
  /* Declarations: */


int  rvs0_F(int  n)
{
  int  retval;

  /* save values of input arguments: */
  rv_UF_F_array[rv_UF_F_count[0]].in_n = n;	/* Generated by:  gen_side0_uf(608)(613)(379)(293)/ rv_temps.cpp:362*/
  /* save values of input globals: */

  /* generate and save values of output arguments and globals: */
  rv_UF_F_array[rv_UF_F_count[0]].out_retval = retval = (int )nondet_long();	/* Generated by:  gen_side0_uf(608)(613)(379)(293)(608)(613)(379)(265)/ rv_temps.cpp:412*/
  rv_UF_F_count[0]++;

  return retval;
}


/*** uninterpreted function side 1: ***/ 
int  rvs1_F(int  n)
{
  int  retval;

  _Bool found = 0;
  _Bool equal = 1;
  int found_ind = -1;
  int rv_uf_ind = rv_UF_F_count[0]-1;
  for(; rv_uf_ind >= 0; rv_uf_ind--) {
    equal = (rv_UF_F_array[rv_uf_ind].in_n == n);	/* Generated by:  gen_side1_uf(608)(613)(379)(273)/ rv_temps.cpp:419*/
    if( equal ) { 
      found = 1;
      found_ind = rv_uf_ind;
      rv_UF_F_array[rv_uf_ind].reach_equiv_flag = 1;
    }
  }

  if( found ) /* input values were found among the saved values */
  {
   /* Sides 0 and 1 are partially equivalent.
    * Returning the results of side 0: */
  retval = rv_UF_F_array[found_ind].out_retval;	/* Generated by:  gen_input_found_case(608)(613)(379)(284)/ rv_temps.cpp:362*/

  } else {

    /* Assert reach-equivalence: side 0 and 1 inputs are equal.*/
    assert( 0 );

  }
  rv_UF_F_count[1]++;

  return retval;
}


typedef struct rv_UF_M_struct_tag {
  int  in_n;	/* Generated by:  gen_uf_item_decl(111)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  out_retval;	/* Generated by:  gen_uf_array(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  _Bool reach_equiv_flag;
} rv_UF_M_struct;
#define rv_UF_K_M 1 /* determined by RVT */
rv_UF_M_struct rv_UF_M_array[rv_UF_K_M];
int rv_UF_M_count[2] = {0,0};


 /*** uninterpreted function side 0: ***/ 
  /* Declarations: */


int  rvs0_M(int  n)
{
  int  retval;

  /* save values of input arguments: */
  rv_UF_M_array[rv_UF_M_count[0]].in_n = n;	/* Generated by:  gen_side0_uf(608)(613)(379)(293)/ rv_temps.cpp:362*/
  /* save values of input globals: */

  /* generate and save values of output arguments and globals: */
  rv_UF_M_array[rv_UF_M_count[0]].out_retval = retval = (int )nondet_long();	/* Generated by:  gen_side0_uf(608)(613)(379)(293)(608)(613)(379)(265)/ rv_temps.cpp:412*/
  rv_UF_M_count[0]++;

  return retval;
}


/*** uninterpreted function side 1: ***/ 
int  rvs1_M(int  n)
{
  int  retval;

  _Bool found = 0;
  _Bool equal = 1;
  int found_ind = -1;
  int rv_uf_ind = rv_UF_M_count[0]-1;
  for(; rv_uf_ind >= 0; rv_uf_ind--) {
    equal = (rv_UF_M_array[rv_uf_ind].in_n == n);	/* Generated by:  gen_side1_uf(608)(613)(379)(273)/ rv_temps.cpp:419*/
    if( equal ) { 
      found = 1;
      found_ind = rv_uf_ind;
      rv_UF_M_array[rv_uf_ind].reach_equiv_flag = 1;
    }
  }

  if( found ) /* input values were found among the saved values */
  {
   /* Sides 0 and 1 are partially equivalent.
    * Returning the results of side 0: */
  retval = rv_UF_M_array[found_ind].out_retval;	/* Generated by:  gen_input_found_case(608)(613)(379)(284)/ rv_temps.cpp:362*/

  } else {

    /* Assert reach-equivalence: side 0 and 1 inputs are equal.*/
    assert( 0 );

  }
  rv_UF_M_count[1]++;

  return retval;
}






void rv_init()
{
}


void rv_check()
{
  /* check reach-equivalence of the inputs for each uninterpreted function: */
  int i;

  /* checking reach-equivalence of all the inputs of array rv_UF_F_array : */
  for (i = rv_UF_F_count[0] - 1; i >= 0; --i)
    assert( rv_UF_F_array[i].reach_equiv_flag );

  /* checking reach-equivalence of all the inputs of array rv_UF_M_array : */
  for (i = rv_UF_M_count[0] - 1; i >= 0; --i)
    assert( rv_UF_M_array[i].reach_equiv_flag );
}

  /* now starting main */

int main()
{
  _Bool equal = 1;
  /* Declarations: */
  int  retval0;	/* Generated by:  gen_retval_declarations/ rv_temps.cpp:269*/
  int  retval1;	/* Generated by:  gen_retval_declarations/ rv_temps.cpp:269*/
  int  rvs0_n;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  rvs1_n;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/


  /* output: */
  /* Allocations for side 0: */
  /* Allocations for side 1: */

  rv_init();

  /* Assume input args are equal: */ 
  rvs0_n = rvs1_n;	/* Generated by:  gen_args_equality(608)(613)(379)(293)/ rv_temps.cpp:362*/

  /* run each side's main() */
  retval0 = chk0_M(rvs0_n);
  retval1 = chk1_M(rvs1_n);

  rv_check();

  return 0;
}

