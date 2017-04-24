/* type-specific outlined function created by prependOutlineFunction() */
int rv_div_int__int_(int x, int y);
/* type-specific outlined function created by prependOutlineFunction() */
unsigned int rv_div_unsigned_long__unsigned_long_(unsigned long x, unsigned long y);
/* type-specific outlined function created by prependOutlineFunction() */
int rv_mult_int__int_(int x, int y);
/* type-specific outlined function created by prependOutlineFunction() */
unsigned int rv_mult_int__unsigned_int_(int x, unsigned int y);
/* type-specific outlined function created by prependOutlineFunction() */
unsigned int rv_mult_unsigned_int__int_(unsigned int x, int y);


enum tg_enFI_all_unit_tests { FI_all_unit_tests_NO_FUNCTION, FI_all_unit_tests };

typedef int  (*rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_7, void  *rv_arg_8);
typedef enum tg_enFI_all_unit_tests  rvt_FuncPtrSubst_void__void_;
float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  isalnum(int  c);
int  isalpha(int  c);
int  iscntrl(int  c);
int  isdigit(int  c);
int  isgraph(int  c);
int  islower(int  c);
int  isprint(int  c);
int  ispunct(int  c);
int  isspace(int  c);
int  isupper(int  c);
int  isxdigit(int  c);
int  tolower(int  c);
int  toupper(int  c);
typedef struct {
  int  top;
  void  *buffer;
  unsigned int  item_length;
} stack_t;
stack_t  *create_stack(unsigned int  item_length);
void  destroy_stack(stack_t  *s);
void  stack_push(stack_t  *s, void  *item);
void  *stack_pop(stack_t  *s);
typedef enum { TT_NONE = 0, TT_IDENT = 1, TT_NUMBER = 2, TT_STRING = 3, TT_EOF = 4, TT_UNKNOWN = 5, TT_OP_AND = 10, TT_OP_OR = 11 } token_type_t;
typedef struct {
  char  *source;
  int  source_index;
  stack_t  *index_stack;
  void  *token_value;
  token_type_t  token_type;
  int  line_number;
} tokenizer_t;
void  init_tokenizer(tokenizer_t  *t, char  *source);
void  release_tokenizer(tokenizer_t  *t);
token_type_t  get_token(tokenizer_t  *t);
void  unget_token(tokenizer_t  *t);
typedef struct {
  tokenizer_t  *t;
} parser_t;
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
int  __CPROVER_printf_2(char  *format, long  opt_arg_0, long  opt_arg_1);
int  __CPROVER_printf_3(char  *format, long  opt_arg_0, long  opt_arg_1, long  opt_arg_2);
int  fprintf_0(FILE  *stream, char  *format);
int  fprintf_1(FILE  *stream, char  *format, long  opt_arg_0);
int  sprintf_0(char  *str, char  *format);
int  sprintf_1(char  *str, char  *format, long  opt_arg_0);
int  sprintf_2(char  *str, char  *format, long  opt_arg_0, long  opt_arg_1);
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
void  seatest_test_fixture_start(char  *filepath);
void  seatest_test_fixture_end(void );
void  seatest_simple_test_result(int  passed, char  *reason, char  *function, unsigned int  line);
void  seatest_assert_true(int  test, char  *function, unsigned int  line);
void  seatest_assert_false(int  test, char  *function, unsigned int  line);
void  seatest_assert_int_equal(int  expected, int  actual, char  *function, unsigned int  line);
void  seatest_assert_float_equal(float  expected, float  actual, float  delta, char  *function, unsigned int  line);
void  seatest_assert_double_equal(double  expected, double  actual, double  delta, char  *function, unsigned int  line);
void  seatest_assert_string_equal(char  *expected, char  *actual, char  *function, unsigned int  line);
void  seatest_assert_string_ends_with(char  *expected, char  *actual, char  *function, unsigned int  line);
void  seatest_assert_string_starts_with(char  *expected, char  *actual, char  *function, unsigned int  line);
void  seatest_assert_string_contains(char  *expected, char  *actual, char  *function, unsigned int  line);
void  seatest_assert_string_doesnt_contain(char  *expected, char  *actual, char  *function, unsigned int  line);
int  seatest_should_run(char  *fixture, char  *test);
void  seatest_run_test(void );
void  seatest_setup();
void  seatest_teardown();
void  fixture_setup(rvt_FuncPtrSubst_void__void_  setup);
void  fixture_teardown(rvt_FuncPtrSubst_void__void_  teardown);
void  fixture_filter(char  *filter);
void  test_filter(char  *filter);
int  run_tests(rvt_FuncPtrSubst_void__void_  tests);
void  assert(_Bool  c);
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
char  *strcpy(char  *dest, char  *src);
char  *strncpy(char  *dest, char  *src, size_t  n);
char  *strcat(char  *dest, char  *src);
char  *strchr(char  *string, int  c);
char  *strncat(char  *dest, char  *src, size_t  n);
int  strcmp(char  *s1, char  *s2);
int  strncmp(char  *s1, char  *s2, size_t  n);
void  *memset(void  *s, int  c, size_t  n);
void  *memcpy(void  *dest, void  *src, size_t  n);
unsigned int  strlen(char  *s);
char  *strdup(char  *s);
char  *strstr(char  *__haystack, char  *__needle);
char  *strtok(char  *str, char  *delim);
char  *memmove(char  *rv_arg_9, char  *rv_arg_10, size_t  rv_arg_11);
int  memcmp(char  *rv_arg_12, char  *rv_arg_13, size_t  rv_arg_14);
int  strncasecmp(char  *rv_arg_15, char  *rv_arg_16, size_t  rv_arg_17);
size_t  strcspn(char  *rv_arg_18, char  *rv_arg_19);
stack_t  *create_stack(unsigned int  item_length);

void  destroy_stack(stack_t  *s);

void  stack_push(stack_t  *s, void  *item);

void  *stack_pop(stack_t  *s);

void  tokenizer_test_fixture(void );
void  parser_test_fixture(void );
void  all_unit_tests();

int  main(int  argc, char  *argv[]);

void  init_parser(parser_t  *p, char  *source);

void  release_parser(parser_t  *p);

void  parse(parser_t  *p);

static void  parser_test1();

void  parser_test_fixture();

unsigned int  GetTickCount();

static int  sea_tests_run = 0;
static int  sea_tests_passed = 0;
static int  sea_tests_failed = 0;
static char  *seatest_current_fixture;
static rvt_FuncPtrSubst_void__void_  seatest_fixture_setup = 0;
static rvt_FuncPtrSubst_void__void_  seatest_fixture_teardown = 0;
void  fixture_setup(rvt_FuncPtrSubst_void__void_  setup);

void  fixture_teardown(rvt_FuncPtrSubst_void__void_  teardown);

void  seatest_setup();

void  seatest_teardown();

char  *test_file_name(char  *path);

static int  seatest_fixture_tests_run;
static int  seatest_fixture_tests_failed;
void  seatest_simple_test_result(int  passed, char  *reason, char  *function, unsigned int  line);

void  seatest_assert_true(int  test, char  *function, unsigned int  line);

void  seatest_assert_false(int  test, char  *function, unsigned int  line);

void  seatest_assert_int_equal(int  expected, int  actual, char  *function, unsigned int  line);

void  seatest_assert_float_equal(float  expected, float  actual, float  delta, char  *function, unsigned int  line);

void  seatest_assert_double_equal(double  expected, double  actual, double  delta, char  *function, unsigned int  line);

void  seatest_assert_string_equal(char  *expected, char  *actual, char  *function, unsigned int  line);

void  seatest_assert_string_ends_with(char  *expected, char  *actual, char  *function, unsigned int  line);

void  seatest_assert_string_starts_with(char  *expected, char  *actual, char  *function, unsigned int  line);

void  seatest_assert_string_contains(char  *expected, char  *actual, char  *function, unsigned int  line);

void  seatest_assert_string_doesnt_contain(char  *expected, char  *actual, char  *function, unsigned int  line);

void  seatest_run_test();

void  seatest_header_printer(char  *s, int  length, char  f);

void  seatest_test_fixture_start(char  *filepath);

void  seatest_test_fixture_end();

static char  *seatest_fixture_filter = 0;
static char  *seatest_test_filter = 0;
void  fixture_filter(char  *filter);

void  test_filter(char  *filter);

int  seatest_should_run(char  *fixture, char  *test);

int  run_tests(rvt_FuncPtrSubst_void__void_  tests);

static int  is_whitespace(char  c);

static int  is_alpha(char  c);

static int  is_alphanum(char  c);

static int  is_digit(char  c);

static struct {
  char  *str;
  token_type_t  token_type;
} keywords[] = { { "and", TT_OP_AND }, { "or", TT_OP_OR } };
void  init_tokenizer(tokenizer_t  *t, char  *source);

void  release_tokenizer(tokenizer_t  *t);

static void  eatwhitespace(tokenizer_t  *t);

static void  tokenize_number(tokenizer_t  *t);

static void  tokenize_identifier(tokenizer_t  *t);

static void  tokenize_string(tokenizer_t  *t);

token_type_t  get_token(tokenizer_t  *t);

void  unget_token(tokenizer_t  *t);

static void  tokenizer_test1();

void  tokenizer_test_fixture();

void  all_unit_tests_hub(enum tg_enFI_all_unit_tests  func_index);
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


stack_t  *create_stack(unsigned int  item_length)
{
  ;
  stack_t  *s = (stack_t *) (malloc(sizeof(stack_t ) ));
  ;
  s->top = 0;
  s->buffer = malloc(rv_mult_int__unsigned_int_(1024,item_length));
  ;
  s->item_length = item_length;
  return s;
}


void  destroy_stack(stack_t  *s)
{
  ;
  ;
  free(s->buffer);
  memset(s,0,sizeof(stack_t ) );
  free(s);
}


void  stack_push(stack_t  *s, void  *item)
{
  ;
  ;
  ;
  unsigned char  *ptr = (unsigned char *) (s->buffer);
  ptr += rv_mult_unsigned_int__int_(s->item_length,s->top);
  memcpy(ptr,item,s->item_length);
  s->top++;
}


void  *stack_pop(stack_t  *s)
{
  ;
  ;
  ;
  unsigned char  *ptr = (unsigned char *) (s->buffer);
  s->top--;
  ptr += rv_mult_unsigned_int__int_(s->item_length,s->top);
  return ptr;
}


void  all_unit_tests()
{
  tokenizer_test_fixture();
  parser_test_fixture();
}


int  main(int  argc, char  *argv[])
{
  run_tests(FI_all_unit_tests);
  return 0;
}


void  init_parser(parser_t  *p, char  *source)
{
  p->t = (tokenizer_t *) (malloc(sizeof(tokenizer_t ) ));
  init_tokenizer(p->t,source);
}


void  release_parser(parser_t  *p)
{
  release_tokenizer(p->t);
  free(p->t);
}


void  parse(parser_t  *p)
{
}


unsigned char  Loop_parser_test1_do_while1(parser_t  **rvp_p);

unsigned char  Loop_parser_test1_do_while2(parser_t  **rvp_p);

unsigned char  Loop_parser_test1_do_while3(parser_t  **rvp_p);

unsigned char  Loop_parser_test1_do_while4(parser_t  **rvp_p);

unsigned char  Loop_parser_test1_do_while5(parser_t  **rvp_p);

unsigned char  Loop_parser_test1_do_while6(parser_t  **rvp_p);


static void  parser_test1()
{
  parser_t  *p = (parser_t *) (malloc(sizeof(parser_t ) ));

  init_parser(p,"1 2 3 4 5");
  {
    Loop_parser_test1_do_while1(&p);
  }

  {
    Loop_parser_test1_do_while2(&p);
  }

  {
    Loop_parser_test1_do_while3(&p);
  }

  {
    Loop_parser_test1_do_while4(&p);
  }

  {
    Loop_parser_test1_do_while5(&p);
  }

  {
    Loop_parser_test1_do_while6(&p);
  }

  release_parser(p);
  free(p);
}

unsigned char  Loop_parser_test1_do_while1(parser_t  **rvp_p)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token((*rvp_p)->t),"<unknown>",329);
  }

  if( 0 )
  {
    return Loop_parser_test1_do_while1(rvp_p);
  }
  return 0;
}

unsigned char  Loop_parser_test1_do_while2(parser_t  **rvp_p)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token((*rvp_p)->t),"<unknown>",330);
  }

  if( 0 )
  {
    return Loop_parser_test1_do_while2(rvp_p);
  }
  return 0;
}

unsigned char  Loop_parser_test1_do_while3(parser_t  **rvp_p)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token((*rvp_p)->t),"<unknown>",331);
  }

  if( 0 )
  {
    return Loop_parser_test1_do_while3(rvp_p);
  }
  return 0;
}

unsigned char  Loop_parser_test1_do_while4(parser_t  **rvp_p)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token((*rvp_p)->t),"<unknown>",332);
  }

  if( 0 )
  {
    return Loop_parser_test1_do_while4(rvp_p);
  }
  return 0;
}

unsigned char  Loop_parser_test1_do_while5(parser_t  **rvp_p)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token((*rvp_p)->t),"<unknown>",333);
  }

  if( 0 )
  {
    return Loop_parser_test1_do_while5(rvp_p);
  }
  return 0;
}

unsigned char  Loop_parser_test1_do_while6(parser_t  **rvp_p)
{
  {
    seatest_assert_int_equal(TT_EOF,get_token((*rvp_p)->t),"<unknown>",334);
  }

  if( 0 )
  {
    return Loop_parser_test1_do_while6(rvp_p);
  }
  return 0;
}



unsigned char  Loop_parser_test_fixture_do_while1();

unsigned char  Loop_parser_test_fixture_do_while2();

unsigned char  Loop_parser_test_fixture_do_while3();


void  parser_test_fixture()
{
  {
    Loop_parser_test_fixture_do_while1();
  }

  {
    Loop_parser_test_fixture_do_while2();
  }

  {
    Loop_parser_test_fixture_do_while3();
  }

}

unsigned char  Loop_parser_test_fixture_do_while1()
{
  {
    seatest_test_fixture_start("/cygdrive/c/gitrvt/test/betik/c5/a.c");
  }

  if( 0 )
  {
    return Loop_parser_test_fixture_do_while1();
  }
  return 0;
}

unsigned char  Loop_parser_test_fixture_do_while2()
{
  {
    if (seatest_should_run("/cygdrive/c/gitrvt/test/betik/c5/a.c","parser_test1"))
    {
      seatest_setup();
      parser_test1();
      seatest_teardown();
      seatest_run_test();
    }

  }

  if( 0 )
  {
    return Loop_parser_test_fixture_do_while2();
  }
  return 0;
}

unsigned char  Loop_parser_test_fixture_do_while3()
{
  {
    seatest_test_fixture_end();
  }

  if( 0 )
  {
    return Loop_parser_test_fixture_do_while3();
  }
  return 0;
}



unsigned int  GetTickCount()
{
  return 0;
}


void  fixture_setup(rvt_FuncPtrSubst_void__void_  setup)
{
  seatest_fixture_setup = setup;
}


void  fixture_teardown(rvt_FuncPtrSubst_void__void_  teardown)
{
  seatest_fixture_teardown = teardown;
}


void  seatest_setup()
{
  if (seatest_fixture_setup != 0)
  {
    all_unit_tests_hub(seatest_fixture_setup);
  }

}


void  seatest_teardown()
{
  if (seatest_fixture_teardown != 0)
  {
    all_unit_tests_hub(seatest_fixture_teardown);
  }

}


unsigned char  Loop_test_file_name_while1(char  **rvp_file, char  **rvp_rvretval);


char  *test_file_name(char  *path)
{
  char  *rvretval = 0;
  char  *file = path + strlen(path);

  {
    Loop_test_file_name_while1(&file,&rvretval);
  }

  if (*file == '\\')
  {
    file++;
  }

  return file;
}

unsigned char  Loop_test_file_name_while1(char  **rvp_file, char  **rvp_rvretval)
{
  char  *path; /* was originally declared outside but is used inside the loop only */
  if( !(*rvp_file != path && **rvp_file != '\\') )
    return 0;

  {
    (*rvp_file)--;
  }

  {
    return Loop_test_file_name_while1(rvp_file,rvp_rvretval);
  }
  return 0;
}



void  seatest_simple_test_result(int  passed, char  *reason, char  *function, unsigned int  line)
{
  if (!passed)
  {
    __CPROVER_printf_3("%-20s Line %-5d %s\r\n",(long ) (function),(long ) (line),(long ) (reason));
    sea_tests_failed++;
  }

  else
  {
    sea_tests_passed++;
  }

}


void  seatest_assert_true(int  test, char  *function, unsigned int  line)
{
  seatest_simple_test_result(test,"Should of been true",function,line);
}


void  seatest_assert_false(int  test, char  *function, unsigned int  line)
{
  seatest_simple_test_result(!test,"Should of been false",function,line);
}


void  seatest_assert_int_equal(int  expected, int  actual, char  *function, unsigned int  line)
{
  char  s[100];

  sprintf_2(s,"Expected %d but was %d",(long ) (expected),(long ) (actual));
  seatest_simple_test_result(expected == actual,s,function,line);
}


void  seatest_assert_float_equal(float  expected, float  actual, float  delta, char  *function, unsigned int  line)
{
  char  s[100];
  float  result = expected - actual;

  sprintf_2(s,"Expected %f but was %f",(long ) (expected),(long ) (actual));
  if (result < 0.0)
  {
    result = 0.0 - result;
  }

  seatest_simple_test_result(result <= delta,s,function,line);
}


void  seatest_assert_double_equal(double  expected, double  actual, double  delta, char  *function, unsigned int  line)
{
  char  s[100];
  double  result = expected - actual;

  sprintf_2(s,"Expected %f but was %f",(long ) (expected),(long ) (actual));
  if (result < 0.0)
  {
    result = 0.0 - result;
  }

  seatest_simple_test_result(result <= delta,s,function,line);
}


void  seatest_assert_string_equal(char  *expected, char  *actual, char  *function, unsigned int  line)
{
  char  s[100];

  sprintf_2(s,"Expected %s but was %s",(long ) (expected),(long ) (actual));
  seatest_simple_test_result(strcmp(expected,actual) == 0,s,function,line);
}


void  seatest_assert_string_ends_with(char  *expected, char  *actual, char  *function, unsigned int  line)
{
  char  s[100];

  sprintf_2(s,"Expected %s to end with %s",(long ) (actual),(long ) (expected));
  seatest_simple_test_result(strcmp(expected,actual + (strlen(actual) - strlen(expected))) == 0,s,function,line);
}


void  seatest_assert_string_starts_with(char  *expected, char  *actual, char  *function, unsigned int  line)
{
  char  s[100];

  sprintf_2(s,"Expected %s to start with %s",(long ) (actual),(long ) (expected));
  seatest_simple_test_result(strncmp(expected,actual,strlen(expected)) == 0,s,function,line);
}


void  seatest_assert_string_contains(char  *expected, char  *actual, char  *function, unsigned int  line)
{
  char  s[100];

  sprintf_2(s,"Expected %s to be in %s",(long ) (expected),(long ) (actual));
  seatest_simple_test_result(strstr(expected,actual) != 0,s,function,line);
}


void  seatest_assert_string_doesnt_contain(char  *expected, char  *actual, char  *function, unsigned int  line)
{
  char  s[100];

  sprintf_2(s,"Expected %s not to have %s in it",(long ) (actual),(long ) (expected));
  seatest_simple_test_result(strstr(expected,actual) == 0,s,function,line);
}


void  seatest_run_test()
{
  sea_tests_run++;
}


unsigned char  Loop_seatest_header_printer_for1(int  d, char  f, int  *rvp_i);

unsigned char  Loop_seatest_header_printer_for2(int  d, char  f, int  l, int  length, int  *rvp_i);


void  seatest_header_printer(char  *s, int  length, char  f)
{
  int  l = strlen(s);
  int  d = rv_div_int__int_(length - (l + 2),2);
  int  i;

  {
    i = 0;
    Loop_seatest_header_printer_for1(d,f,&i);
  }

  __CPROVER_printf_1(" %s ",(long ) (s));
  {
    i = d + l + 2;
    Loop_seatest_header_printer_for2(d,f,l,length,&i);
  }

  __CPROVER_printf_0("\r\n");
}

unsigned char  Loop_seatest_header_printer_for1(int  d, char  f, int  *rvp_i)
{
  if( !(*rvp_i < d) )
    return 0;

  {
    __CPROVER_printf_1("%c",(long ) (f));
  }

  (*rvp_i)++;
  {
    return Loop_seatest_header_printer_for1(d,f,rvp_i);
  }
  return 0;
}

unsigned char  Loop_seatest_header_printer_for2(int  d, char  f, int  l, int  length, int  *rvp_i)
{
  if( !(*rvp_i < length) )
    return 0;

  {
    __CPROVER_printf_1("%c",(long ) (f));
  }

  (*rvp_i)++;
  {
    return Loop_seatest_header_printer_for2(d,f,l,length,rvp_i);
  }
  return 0;
}



void  seatest_test_fixture_start(char  *filepath)
{
  seatest_current_fixture = test_file_name(filepath);
  seatest_header_printer(seatest_current_fixture,50,'-');
  seatest_fixture_tests_failed = sea_tests_failed;
  seatest_fixture_tests_run = sea_tests_run;
  seatest_fixture_teardown = 0;
  seatest_fixture_setup = 0;
}


void  seatest_test_fixture_end()
{
  char  s[100];

  sprintf_2(s,"%d run  %d failed",(long ) (sea_tests_run - seatest_fixture_tests_run),(long ) (sea_tests_failed - seatest_fixture_tests_failed));
  seatest_header_printer(s,50,' ');
  __CPROVER_printf_0("\r\n");
}


void  fixture_filter(char  *filter)
{
  seatest_fixture_filter = filter;
}


void  test_filter(char  *filter)
{
  seatest_test_filter = filter;
}


int  seatest_should_run(char  *fixture, char  *test)
{
  int  run = 1;

  if (seatest_fixture_filter)
  {
    if (strncmp(seatest_fixture_filter,fixture,strlen(seatest_fixture_filter)) != 0)
    {
      run = 0;
    }

  }

  if (seatest_test_filter)
  {
    if (strncmp(seatest_test_filter,test,strlen(seatest_test_filter)) != 0)
    {
      run = 0;
    }

  }

  return run;
}


int  run_tests(rvt_FuncPtrSubst_void__void_  tests)
{
  unsigned long  end;
  unsigned long  start = GetTickCount();

  all_unit_tests_hub(tests);
  end = GetTickCount();
  __CPROVER_printf_0("\r\n\r\n==================================================\r\n");
  if (sea_tests_failed > 0)
  {
    __CPROVER_printf_0("                      Failed\r\n");
  }

  else
  {
    __CPROVER_printf_0("               ALL TESTS PASSED\r\n");
  }

  __CPROVER_printf_1("                 %d tests run\r\n",(long ) (sea_tests_run));
  __CPROVER_printf_1("                    in %d ms\r\n",(long ) (end - start));
  __CPROVER_printf_0("==================================================\r\n");
  getchar();
  return sea_tests_failed == 0;
}


static int  is_whitespace(char  c)
{
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}


static int  is_alpha(char  c)
{
  if (c < 0)
  {
    return 1;
  }

  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}


static int  is_alphanum(char  c)
{
  return is_alpha(c) || isdigit(c);
}


static int  is_digit(char  c)
{
  return c >= '0' && c <= '9';
}


void  init_tokenizer(tokenizer_t  *t, char  *source)
{
  t->source = (char *) (malloc(strlen(source) + 1));
  strcpy(t->source,source);
  t->source_index = 0;
  t->index_stack = create_stack(sizeof(int ) );
  t->token_value = (void *) (0);
  t->token_type = TT_NONE;
  t->line_number = 1;
}


void  release_tokenizer(tokenizer_t  *t)
{
  free(t->source);
  free(t->token_value);
  destroy_stack(t->index_stack);
  memset(t,0,sizeof(tokenizer_t ) );
}


static void  eatwhitespace(tokenizer_t  *t)
{
eatwhitespace_begin:
  t->source_index++;
}


unsigned char  Loop_tokenize_number_while1(tokenizer_t  **rvp_t);


static void  tokenize_number(tokenizer_t  *t)
{
  t->token_type == TT_NUMBER;
  t->token_value = malloc(sizeof(int ) );
  *((int *) (t->token_value)) = t->source[t->source_index++] - '0';
  {
    Loop_tokenize_number_while1(&t);
  }

}

unsigned char  Loop_tokenize_number_while1(tokenizer_t  **rvp_t)
{
  if( !(is_digit((*rvp_t)->source[(*rvp_t)->source_index])) )
    return 0;

  {
    *((int *) ((*rvp_t)->token_value)) = rv_mult_int__int_(*((int *) ((*rvp_t)->token_value)),10);
    *((int *) ((*rvp_t)->token_value)) += (*rvp_t)->source[(*rvp_t)->source_index] - '0';
  }

  {
    return Loop_tokenize_number_while1(rvp_t);
  }
  return 0;
}



unsigned char  Loop_tokenize_identifier_while1(int  *rvp_i, tokenizer_t  **rvp_t);

unsigned char  Loop_tokenize_identifier_for2(int  *rvp_i, tokenizer_t  **rvp_t);


static void  tokenize_identifier(tokenizer_t  *t)
{
  int  i = 0;

  t->token_value = (char *) (malloc(64));
  ((char *) (t->token_value))[i++] = t->source[t->source_index++];
  {
    Loop_tokenize_identifier_while1(&i,&t);
  }

  ((char *) (t->token_value))[i] = '\0';
  {
    i = 0;
    switch (Loop_tokenize_identifier_for2(&i,&t))
    {
    case 123:
      return;
    case 0:
      break;
    }

  }

  t->token_type = TT_IDENT;
}

unsigned char  Loop_tokenize_identifier_while1(int  *rvp_i, tokenizer_t  **rvp_t)
{
  if( !(is_alphanum((*rvp_t)->source[(*rvp_t)->source_index])) )
    return 0;

  {
    ((char *) ((*rvp_t)->token_value))[(*rvp_i)++] = (*rvp_t)->source[(*rvp_t)->source_index++];
    if (64 == *rvp_i)
    {
      fprintf_1(stderr,"MAX_IDENT_LENGTH reached :%d\n",(long ) ((*rvp_t)->line_number));
      exit(1);
    }

  }

  {
    return Loop_tokenize_identifier_while1(rvp_i,rvp_t);
  }
  return 0;
}

unsigned char  Loop_tokenize_identifier_for2(int  *rvp_i, tokenizer_t  **rvp_t)
{
  if( !(*rvp_i < rv_div_unsigned_long__unsigned_long_(sizeof(keywords) ,sizeof(keywords[0]) )) )
    return 0;

  {
    if (strcmp((char *) ((*rvp_t)->token_value),keywords[*rvp_i].str) == 0)
    {
      (*rvp_t)->token_type = keywords[*rvp_i].token_type;
      {
        return 123;
      }

    }

  }

  ++*rvp_i;
  {
    return Loop_tokenize_identifier_for2(rvp_i,rvp_t);
  }
  return 0;
}



unsigned char  Loop_tokenize_string_while1(int  *rvp_i, tokenizer_t  **rvp_t);


static void  tokenize_string(tokenizer_t  *t)
{
  int  i = 0;

  t->token_value = malloc(1024);
  t->source_index++;
  {
    Loop_tokenize_string_while1(&i,&t);
  }

  ((char *) (t->token_value))[i] = '\0';
  t->source_index++;
  t->token_type = TT_STRING;
}

unsigned char  Loop_tokenize_string_while1(int  *rvp_i, tokenizer_t  **rvp_t)
{
  if( !((*rvp_t)->source[(*rvp_t)->source_index] != '"') )
    return 0;

  {
    if ((*rvp_t)->source[(*rvp_t)->source_index] == '\\')
    {
      if ((*rvp_t)->source[(*rvp_t)->source_index + 1] == 'n')
      {
        ((char *) ((*rvp_t)->token_value))[(*rvp_i)++] = '\n';
        (*rvp_t)->source_index += 2;
      }

      else
      {
        if ((*rvp_t)->source[(*rvp_t)->source_index + 1] == '"')
        {
          ((char *) ((*rvp_t)->token_value))[(*rvp_i)++] = '"';
          (*rvp_t)->source_index += 2;
        }

        else
        {
          if ((*rvp_t)->source[(*rvp_t)->source_index + 1] == '\\')
          {
            ((char *) ((*rvp_t)->token_value))[(*rvp_i)++] = '\\';
            (*rvp_t)->source_index += 2;
          }

          else
          {
            ((char *) ((*rvp_t)->token_value))[(*rvp_i)++] = '\\';
            (*rvp_t)->source_index++;
          }

        }

      }

    }

    else
    {
      ((char *) ((*rvp_t)->token_value))[(*rvp_i)++] = (*rvp_t)->source[(*rvp_t)->source_index++];
    }

    if (*rvp_i >= 1024)
    {
      fprintf_0(stderr,"max inline string length reached\n");
      exit(1);
    }

  }

  {
    return Loop_tokenize_string_while1(rvp_i,rvp_t);
  }
  return 0;
}



token_type_t  get_token(tokenizer_t  *t)
{
  if (t->token_value)
  {
    free(t->token_value);
  }

  t->token_value = (void *) (0);
  eatwhitespace(t);
  stack_push(t->index_stack,&t->source_index);
  if ('\0' == t->source[t->source_index])
  {
    t->token_type = TT_EOF;
    return TT_EOF;
  }

  if (is_digit(t->source[t->source_index]))
  {
    tokenize_number(t);
    return TT_NUMBER;
  }

  if (is_alpha(t->source[t->source_index]))
  {
    tokenize_identifier(t);
    return TT_IDENT;
  }

  if ('"' == t->source[t->source_index])
  {
    tokenize_string(t);
    return TT_STRING;
  }

  return TT_UNKNOWN;
}


unsigned char  Loop_unget_token_do_while1(int  prev_source_index, tokenizer_t  **rvp_t);


void  unget_token(tokenizer_t  *t)
{
  int  prev_source_index = *((int *) (stack_pop(t->index_stack)));

  if (t->source_index <= prev_source_index)
  {
    t->source_index = prev_source_index;
    return;
  }

  {
    Loop_unget_token_do_while1(prev_source_index,&t);
  }

}

unsigned char  Loop_unget_token_do_while1(int  prev_source_index, tokenizer_t  **rvp_t)
{
  {
    (*rvp_t)->source_index--;
    if ('\n' == (*rvp_t)->source[(*rvp_t)->source_index])
    {
      (*rvp_t)->line_number--;
    }

  }

  if( (*rvp_t)->source_index > prev_source_index )
  {
    return Loop_unget_token_do_while1(prev_source_index,rvp_t);
  }
  return 0;
}



unsigned char  Loop_tokenizer_test1_do_while1(tokenizer_t  **rvp_t);

unsigned char  Loop_tokenizer_test1_do_while2(tokenizer_t  **rvp_t);

unsigned char  Loop_tokenizer_test1_do_while3(tokenizer_t  **rvp_t);

unsigned char  Loop_tokenizer_test1_do_while4(tokenizer_t  **rvp_t);

unsigned char  Loop_tokenizer_test1_do_while5(tokenizer_t  **rvp_t);

unsigned char  Loop_tokenizer_test1_do_while6(tokenizer_t  **rvp_t);


static void  tokenizer_test1()
{
  tokenizer_t  *t = (tokenizer_t *) (malloc(sizeof(tokenizer_t ) ));

  init_tokenizer(t," 1 \"asd\" 3");
  {
    Loop_tokenizer_test1_do_while1(&t);
  }

  {
    Loop_tokenizer_test1_do_while2(&t);
  }

  {
    Loop_tokenizer_test1_do_while3(&t);
  }

  unget_token(t);
  unget_token(t);
  unget_token(t);
  {
    Loop_tokenizer_test1_do_while4(&t);
  }

  {
    Loop_tokenizer_test1_do_while5(&t);
  }

  {
    Loop_tokenizer_test1_do_while6(&t);
  }

  release_tokenizer(t);
  free(t);
}

unsigned char  Loop_tokenizer_test1_do_while1(tokenizer_t  **rvp_t)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token(*rvp_t),"<unknown>",805);
  }

  if( 0 )
  {
    return Loop_tokenizer_test1_do_while1(rvp_t);
  }
  return 0;
}

unsigned char  Loop_tokenizer_test1_do_while2(tokenizer_t  **rvp_t)
{
  {
    seatest_assert_int_equal(TT_STRING,get_token(*rvp_t),"<unknown>",806);
  }

  if( 0 )
  {
    return Loop_tokenizer_test1_do_while2(rvp_t);
  }
  return 0;
}

unsigned char  Loop_tokenizer_test1_do_while3(tokenizer_t  **rvp_t)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token(*rvp_t),"<unknown>",807);
  }

  if( 0 )
  {
    return Loop_tokenizer_test1_do_while3(rvp_t);
  }
  return 0;
}

unsigned char  Loop_tokenizer_test1_do_while4(tokenizer_t  **rvp_t)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token(*rvp_t),"<unknown>",811);
  }

  if( 0 )
  {
    return Loop_tokenizer_test1_do_while4(rvp_t);
  }
  return 0;
}

unsigned char  Loop_tokenizer_test1_do_while5(tokenizer_t  **rvp_t)
{
  {
    seatest_assert_int_equal(TT_STRING,get_token(*rvp_t),"<unknown>",812);
  }

  if( 0 )
  {
    return Loop_tokenizer_test1_do_while5(rvp_t);
  }
  return 0;
}

unsigned char  Loop_tokenizer_test1_do_while6(tokenizer_t  **rvp_t)
{
  {
    seatest_assert_int_equal(TT_NUMBER,get_token(*rvp_t),"<unknown>",813);
  }

  if( 0 )
  {
    return Loop_tokenizer_test1_do_while6(rvp_t);
  }
  return 0;
}



unsigned char  Loop_tokenizer_test_fixture_do_while1();

unsigned char  Loop_tokenizer_test_fixture_do_while2();

unsigned char  Loop_tokenizer_test_fixture_do_while3();


void  tokenizer_test_fixture()
{
  {
    Loop_tokenizer_test_fixture_do_while1();
  }

  {
    Loop_tokenizer_test_fixture_do_while2();
  }

  {
    Loop_tokenizer_test_fixture_do_while3();
  }

}

unsigned char  Loop_tokenizer_test_fixture_do_while1()
{
  {
    seatest_test_fixture_start("/cygdrive/c/gitrvt/test/betik/c5/a.c");
  }

  if( 0 )
  {
    return Loop_tokenizer_test_fixture_do_while1();
  }
  return 0;
}

unsigned char  Loop_tokenizer_test_fixture_do_while2()
{
  {
    if (seatest_should_run("/cygdrive/c/gitrvt/test/betik/c5/a.c","tokenizer_test1"))
    {
      seatest_setup();
      tokenizer_test1();
      seatest_teardown();
      seatest_run_test();
    }

  }

  if( 0 )
  {
    return Loop_tokenizer_test_fixture_do_while2();
  }
  return 0;
}

unsigned char  Loop_tokenizer_test_fixture_do_while3()
{
  {
    seatest_test_fixture_end();
  }

  if( 0 )
  {
    return Loop_tokenizer_test_fixture_do_while3();
  }
  return 0;
}




void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
void  all_unit_tests_hub(enum tg_enFI_all_unit_tests  func_index)
{
  switch( func_index ) {
    case FI_all_unit_tests: return all_unit_tests();
    /* Check: the func index is valid: */
    default: __CPROVER_assume (0);
  }

}


