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
struct __FILE {
  int  flags;
};
typedef struct __FILE  FILE;
extern FILE  *stdin;
extern FILE  *stdout;
extern FILE  *stderr;

/*** global declarations side 0: ***/
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
int  rvs0_fflush(FILE  *stream);
int  rvs0___CPROVER_printf_0(char  *format);
int  rvs0___CPROVER_printf_1(char  *format, long  opt_arg_0);
int  rvs0_fprintf_0(FILE  *stream, char  *format);
int  rvs0_sprintf_0(char  *str, char  *format);
int  rvs0_snprintf_0(char  *str, unsigned int  size, char  *format);
int  rvs0_vsprintf_0(char  *rv_arg_0, char  *rv_arg_1);
int  rvs0_vprintf_0(char  *rv_arg_2);
int  rvs0_vfprintf_0(FILE  *rv_arg_3, char  *rv_arg_4);
int  rvs0_scanf_0(char  *format);
int  rvs0_fscanf_0(FILE  *stream, char  *format);
int  rvs0_sscanf_0(char  *str, char  *format);
size_t  rvs0_fread(void  *ptr, size_t  size, size_t  nmemb, FILE  *stream);
size_t  rvs0_fwrite(void  *ptr, size_t  size, size_t  nmemb, FILE  *stream);
int  rvs0_fseek(FILE  *stream, long  off, int  whence);
FILE  *rvs0_fopen(char  *path, char  *mode);
FILE  *rvs0_fdopen(int  fildes, char  *mode);
FILE  *rvs0_freopen(char  *path, char  *mode, FILE  *stream);
long  rvs0_ftell(FILE  *rv_arg_5);
int  rvs0_fclose(FILE  *stream);
int  rvs0_fgetc(FILE  *stream);
char  *rvs0_fgets(char  *s, int  size, FILE  *stream);
int  rvs0_getc(FILE  *stream);
int  rvs0_getchar();
char  *rvs0_gets(char  *s);
int  rvs0_ungetc(int  c, FILE  *stream);
int  rvs0_fputc(int  c, FILE  *stream);
int  rvs0_fputs(char  *s, FILE  *stream);
int  rvs0_putc(int  c, FILE  *stream);
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
int  rvs1_fflush(FILE  *stream);
int  rvs1___CPROVER_printf_0(char  *format);
int  rvs1___CPROVER_printf_1(char  *format, long  opt_arg_0);
int  rvs1_fprintf_0(FILE  *stream, char  *format);
int  rvs1_sprintf_0(char  *str, char  *format);
int  rvs1_snprintf_0(char  *str, unsigned int  size, char  *format);
int  rvs1_vsprintf_0(char  *rv_arg_7, char  *rv_arg_8);
int  rvs1_vprintf_0(char  *rv_arg_9);
int  rvs1_vfprintf_0(FILE  *rv_arg_10, char  *rv_arg_11);
int  rvs1_scanf_0(char  *format);
int  rvs1_fscanf_0(FILE  *stream, char  *format);
int  rvs1_sscanf_0(char  *str, char  *format);
size_t  rvs1_fread(void  *ptr, size_t  size, size_t  nmemb, FILE  *stream);
size_t  rvs1_fwrite(void  *ptr, size_t  size, size_t  nmemb, FILE  *stream);
int  rvs1_fseek(FILE  *stream, long  off, int  whence);
FILE  *rvs1_fopen(char  *path, char  *mode);
FILE  *rvs1_fdopen(int  fildes, char  *mode);
FILE  *rvs1_freopen(char  *path, char  *mode, FILE  *stream);
long  rvs1_ftell(FILE  *rv_arg_12);
int  rvs1_fclose(FILE  *stream);
int  rvs1_fgetc(FILE  *stream);
char  *rvs1_fgets(char  *s, int  size, FILE  *stream);
int  rvs1_getc(FILE  *stream);
int  rvs1_getchar();
char  *rvs1_gets(char  *s);
int  rvs1_ungetc(int  c, FILE  *stream);
int  rvs1_fputc(int  c, FILE  *stream);
int  rvs1_fputs(char  *s, FILE  *stream);
int  rvs1_putc(int  c, FILE  *stream);
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
  {
    return 0;
  }

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
  {
    return 0;
  }

  return rvs1_plusone(n) - 1 - rvs1_G(rvs1_M(n - 1));
}

int  rvs1_G(int  n)
{
  return rvs1_F(n);
}


/* Implementations of the uninterpreted functions: */
#define rv_UF_K_F 5
//Recording arrays for local parameter input
int  rvt_token_F_n[rv_UF_K_F];

//Recording arrays for global input

//Output arrays for local input
int  rvt_token_F_n_output[rv_UF_K_F];


//Output arrays for global input

//Output array for function output
int  rvt_token_F_retval_output[rv_UF_K_F];

int  rvt_token_F_call_mark_array0[rv_UF_K_F];
int  rvt_token_F_call_mark_array1[rv_UF_K_F];
int  rvt_token_F_count;
_Bool  rvt_token_F_first_call_to_uf_flag;

 /*** uninterpreted function side 0: ***/ 
int  rvs0_F(int  n)
{
  int  retval;

 /* Zeroing both mark arrays and count variable for unitrv mutual termination check */
  /* save values of input arguments: */
	rvt_token_F_n[rvt_token_F_count] = n;
  /* save values of input globals: */

  /* generate and save values of output arguments and globals: */

  /* generate and save value for the functino output : */
  rvt_token_F_retval_output[rvt_token_F_count] = retval = (int )nondet_long();	/* Generated by:  RVReUfGen::gen_unitrv_side0_uf(615)(620)(386)(267)/ c:\newrvt\rv_temps.cpp:420*/
	rvt_token_F_call_mark_array0[rvt_token_F_count] = 1;
	rvt_token_F_count++;
  return retval;
}


/*** uninterpreted function side 1: ***/ 
int  rvs1_F(int  n)
{
  int  retval;

  _Bool found = 0;
  _Bool equal = 1;
  int found_ind = -1;
  int rv_uf_ind = rvt_token_F_count-1;
  for(; rv_uf_ind >= 0; rv_uf_ind--) {
		equal = equal && n == rvt_token_F_n[rv_uf_ind];
    if( equal ) { 
      found = 1;
      found_ind = rv_uf_ind;
		rvt_token_F_call_mark_array1[rv_uf_ind] = 1;
    }
		equal = 1;
  }

  if( found ) /* input values were found among the saved values */
  {
   /* Sides 0 and 1 are partially equivalent.
    * Returning the results of side 0: */
  retval = rvt_token_F_retval_output[rv_uf_ind];	/* Generated by:  RVReUfGen::gen_unitrv_input_found_case(615)(620)(386)(290)/ c:\newrvt\rv_temps.cpp:362*/

  } else {

    /* Assert reach-equivalence: side 0 and 1 inputs are equal.*/
    assert( 0 );

  }

  return retval;
}

void rvt_token_initialize_mutual_termination_tokens_F(){
	int rvt_token_i = 0;
		for (rvt_token_i = 0 ; rvt_token_i < rv_UF_K_F ; rvt_token_i++){
			rvt_token_F_call_mark_array0[rvt_token_i] = 0;
			rvt_token_F_call_mark_array1[rvt_token_i] = 0;
		}
		rvt_token_F_count = 0;
		rvt_token_F_first_call_to_uf_flag = 0;

}
#define rv_UF_K_M 5
//Recording arrays for local parameter input
int  rvt_token_M_n[rv_UF_K_M];

//Recording arrays for global input

//Output arrays for local input
int  rvt_token_M_n_output[rv_UF_K_M];


//Output arrays for global input

//Output array for function output
int  rvt_token_M_retval_output[rv_UF_K_M];

int  rvt_token_M_call_mark_array0[rv_UF_K_M];
int  rvt_token_M_call_mark_array1[rv_UF_K_M];
int  rvt_token_M_count;
_Bool  rvt_token_M_first_call_to_uf_flag;

 /*** uninterpreted function side 0: ***/ 
int  rvs0_M(int  n)
{
  int  retval;

 /* Zeroing both mark arrays and count variable for unitrv mutual termination check */
  /* save values of input arguments: */
	rvt_token_M_n[rvt_token_M_count] = n;
  /* save values of input globals: */

  /* generate and save values of output arguments and globals: */

  /* generate and save value for the functino output : */
  rvt_token_M_retval_output[rvt_token_M_count] = retval = (int )nondet_long();	/* Generated by:  RVReUfGen::gen_unitrv_side0_uf(615)(620)(386)(267)/ c:\newrvt\rv_temps.cpp:420*/
	rvt_token_M_call_mark_array0[rvt_token_M_count] = 1;
	rvt_token_M_count++;
  return retval;
}


/*** uninterpreted function side 1: ***/ 
int  rvs1_M(int  n)
{
  int  retval;

  _Bool found = 0;
  _Bool equal = 1;
  int found_ind = -1;
  int rv_uf_ind = rvt_token_M_count-1;
  for(; rv_uf_ind >= 0; rv_uf_ind--) {
		equal = equal && n == rvt_token_M_n[rv_uf_ind];
    if( equal ) { 
      found = 1;
      found_ind = rv_uf_ind;
		rvt_token_M_call_mark_array1[rv_uf_ind] = 1;
    }
		equal = 1;
  }

  if( found ) /* input values were found among the saved values */
  {
   /* Sides 0 and 1 are partially equivalent.
    * Returning the results of side 0: */
  retval = rvt_token_M_retval_output[rv_uf_ind];	/* Generated by:  RVReUfGen::gen_unitrv_input_found_case(615)(620)(386)(290)/ c:\newrvt\rv_temps.cpp:362*/

  } else {

    /* Assert reach-equivalence: side 0 and 1 inputs are equal.*/
    assert( 0 );

  }

  return retval;
}

void rvt_token_initialize_mutual_termination_tokens_M(){
	int rvt_token_i = 0;
		for (rvt_token_i = 0 ; rvt_token_i < rv_UF_K_M ; rvt_token_i++){
			rvt_token_M_call_mark_array0[rvt_token_i] = 0;
			rvt_token_M_call_mark_array1[rvt_token_i] = 0;
		}
		rvt_token_M_count = 0;
		rvt_token_M_first_call_to_uf_flag = 0;

}
