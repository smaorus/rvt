

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
struct __FILE {
  int  flags;
};
typedef struct __FILE  FILE;
int  fflush(FILE  *stream);
extern FILE  *stdin;
extern FILE  *stdout;
extern FILE  *stderr;
int  __CPROVER_printf_0(char  *format);
int  __CPROVER_printf_1(char  *format, long  opt_arg_0);
int  fprintf_0(FILE  *stream, char  *format);
int  sprintf_0(char  *str, char  *format);
int  snprintf_0(char  *str, unsigned int  size, char  *format);
int  vsprintf_0(char  *rv_arg_0, char  *rv_arg_1);
int  vprintf_0(char  *rv_arg_2);
int  vfprintf_0(FILE  *rv_arg_3, char  *rv_arg_4);
int  scanf_0(char  *format);
int  fscanf_0(FILE  *stream, char  *format);
int  sscanf_0(char  *str, char  *format);
size_t  fread(void  *ptr, size_t  size, size_t  nmemb, FILE  *stream);
size_t  fwrite(void  *ptr, size_t  size, size_t  nmemb, FILE  *stream);
int  fseek(FILE  *stream, long  off, int  whence);
FILE  *fopen(char  *path, char  *mode);
FILE  *fdopen(int  fildes, char  *mode);
FILE  *freopen(char  *path, char  *mode, FILE  *stream);
long  ftell(FILE  *rv_arg_5);
int  fclose(FILE  *stream);
int  fgetc(FILE  *stream);
char  *fgets(char  *s, int  size, FILE  *stream);
int  getc(FILE  *stream);
int  getchar();
char  *gets(char  *s);
int  ungetc(int  c, FILE  *stream);
int  fputc(int  c, FILE  *stream);
int  fputs(char  *s, FILE  *stream);
int  putc(int  c, FILE  *stream);
int  remove(char  *rv_arg_6);
int  link(char  *path1, char  *path2);
extern int  putchar(int  c);

extern int  puts(char  *s);

void  perror(char  *s);
int  F(int  n);
int  M(int  n);
int  F(int  n);

int  M(int  n);

int  main();

extern int  putchar(int  c)
{
__CPROVER_HIDE:
  __CPROVER_printf_1("%c\n",(long ) (c));
}


extern int  puts(char  *s)
{
__CPROVER_HIDE:
  __CPROVER_printf_1("%s\n",(long ) (s));
}


int  F(int  n)
{
  if (n == 0)
  {
    return 1;
  }

  return n - M(F(n - 1));
}


int  M(int  n)
{
  if (n == 0)
  {
    return 0;
  }

  return n - F(M(n - 1));
}


unsigned char  Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);

unsigned char  Loop_main_for2(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval);


int  main()
{
  int  rvretval = 0;
  int  i;
  int  l = 0;

  {
    i = 0;
    switch (Loop_main_for1(&i,&l,&rvretval))
    {
    case 123:
      return rvretval;
    case 0:
      break;
    }

  }

  __CPROVER_printf_0("\n");
  {
    i = 0;
    Loop_main_for2(&i,&l,&rvretval);
  }

  __CPROVER_printf_0("\n");
  return l;
}

unsigned char  Loop_main_for1(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval)
{
  if( !(*rvp_i < 20) )
    return 0;

  {
    __CPROVER_printf_1("%2d ",(long ) (F(*rvp_i)));
    (*rvp_l)++;
    if (*rvp_i > 20)
    {
      {
        *rvp_rvretval = 3;
        return 123;
      }

    }

  }

  (*rvp_i)++;
  return 0;
}

unsigned char  Loop_main_for2(int  *rvp_i, int  *rvp_l, int  *rvp_rvretval)
{
  if( !(*rvp_i < 20) )
    return 0;

  {
    __CPROVER_printf_1("%2d ",(long ) (M(*rvp_i)));
    (*rvp_l)++;
  }

  (*rvp_i)++;
  return 0;
}




void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
