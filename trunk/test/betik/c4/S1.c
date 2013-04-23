/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./a1.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./a1.c"
# 17 "./a1.c"
struct stack {
 int top;
 void* buffer;
 unsigned item_length;
};


struct stack* create_stack(unsigned item_length);
void destroy_stack(struct stack* s);
void stack_push(struct stack* s, void* item);
const void* stack_pop(struct stack* s);
# 47 "./a1.c"
enum token_type {
 TT_NONE= 0,
 TT_IDENT= 1,
 TT_NUMBER= 2,
 TT_STRING= 3,
 TT_EOF= 4,
 TT_UNKNOWN= 5,
 TT_OP_AND= 10,
 TT_OP_OR= 11,
};


struct tokenizer {
 char* source;
 int source_index;
 struct stack* index_stack;
 void* token_value;
 enum token_type token_type;
 int line_number;
};


void init_tokenizer(struct tokenizer* t, char* source);
void release_tokenizer(struct tokenizer* t);
enum token_type get_token(struct tokenizer* t);
void unget_token(struct tokenizer* t);
# 99 "./a1.c"
# 1 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/stdio.h" 1



# 1 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/sys/types.h" 1



typedef int pid_t;
typedef unsigned int size_t;
typedef unsigned char u_char;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;

typedef unsigned int off_t;
typedef unsigned int mode_t;
# 25 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/sys/types.h"
typedef unsigned int u_int;

typedef int uid_t;
# 5 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/stdio.h" 2





struct __FILE
{
  int flags;
};





typedef struct __FILE FILE;

int fflush(FILE *stream);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int __CPROVER_printf(const char *format, ...);
# 38 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/stdio.h"
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, unsigned size, const char *format, ...);
int vsprintf(char *, const char*, ...);
int vprintf(const char*, ...);
int vfprintf(FILE*, const char*, ...);

int scanf( const char *format, ...);
int fscanf( FILE *stream, const char *format, ...);
int sscanf( const char *str, const char *format, ...);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fseek (FILE *stream, long int off, int whence);

FILE *fopen (const char *path, const char *mode);
FILE *fdopen (int fildes, const char *mode);
FILE *freopen (const char *path, const char *mode, FILE *stream);

long ftell(FILE *);

int fclose(FILE *stream);

int fgetc(FILE *stream);
char *fgets(char *s, int size, FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *s);
int ungetc(int c, FILE *stream);

int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);
int putc(int c, FILE *stream);

int remove(const char*);
int link(const char *path1, const char *path2);

extern inline int putchar(int c)
{
  __CPROVER_HIDE:
  __CPROVER_printf("%c\n", c);
}

extern inline int puts(const char *s)
{
  __CPROVER_HIDE:
  __CPROVER_printf("%s\n", s);
}

void perror(const char *s);
# 100 "./a1.c" 2





void seatest_test_fixture_start(char* filepath);
void seatest_test_fixture_end( void );
void seatest_simple_test_result(int passed, char* reason, const char* function, unsigned int line);
void seatest_assert_true(int test, const char* function, unsigned int line);
void seatest_assert_false(int test, const char* function, unsigned int line);
void seatest_assert_int_equal(int expected, int actual, const char* function, unsigned int line);
void seatest_assert_float_equal(float expected, float actual, float delta, const char* function, unsigned int line);
void seatest_assert_double_equal(double expected, double actual, double delta, const char* function, unsigned int line);
void seatest_assert_string_equal(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_ends_with(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_starts_with(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_contains(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_doesnt_contain(char* expected, char* actual, const char* function, unsigned int line);
int seatest_should_run( char* fixture, char* test);
void seatest_run_test(void);
void seatest_setup();
void seatest_teardown();
# 147 "./a1.c"
void fixture_setup(void (*setup)( void ));
void fixture_teardown(void (*teardown)( void ));



void fixture_filter(char* filter);
void test_filter(char* filter);

int run_tests(void (*tests)(void));
# 175 "./a1.c"
# 1 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/assert.h" 1






void assert(_Bool c);
# 176 "./a1.c" 2
# 1 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/stdlib.h" 1
# 14 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/stdlib.h"
void exit(int status);
char *getenv(const char *name);
int system(const char *string);
void abort(void);

void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);
long long atoq(const char *nptr);

float atof(const char *nptr);

int rand(void);
void srand(unsigned int seed);

long int random(void);
void srandom(unsigned int seed);
char *initstate(unsigned int seed, char *state, size_t n);
char *setstate(char *state);

int mkstemp (const char* temp);

void qsort(void * base, size_t num, size_t width,
           int (*fncompare)(const void *, const void *) );
# 177 "./a1.c" 2
# 1 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/string.h" 1
# 10 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/string.h"
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strchr ( const char * string, int c );
char *strncat(char *dest, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
unsigned strlen(const char *s);
char *strdup(const char *s);
char *strstr(const char *__haystack, const char *__needle);
char *strtok ( const char *str, const char * delim);

char *memmove(char*, const char*, size_t);
int memcmp(const char*, const char*, size_t);
int strncasecmp(const char*, const char*, size_t);
size_t strcspn(const char*, const char*);
# 178 "./a1.c" 2
# 1 "/home/edima/rv/Debug/../tools/scripts/../ansi-c-lib/ctype.h" 1



int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);
# 179 "./a1.c" 2




struct stack* create_stack(unsigned item_length)
{
 assert(item_length != 0);

 struct stack* s = (struct stack*)malloc(sizeof(struct stack));

 assert(s);

 s->top = 0;
 s->buffer = malloc(1024 * item_length);

 assert(s->buffer != ((void *)0));

 s->item_length = item_length;

 return s;
}

void destroy_stack(struct stack* s)
{
 assert(s);
 assert(s->buffer);

 free(s->buffer);
 memset(s, 0, sizeof(struct stack));
 free(s);
}

void stack_push(struct stack* s, void* item)
{
 assert(s);
 assert(s->buffer);
 assert(item);

 unsigned char* ptr = (unsigned char*)s->buffer;
 ptr += s->item_length * s->top;
 memcpy(ptr, item, s->item_length);
 s->top++;
}

const void* stack_pop(struct stack* s)
{
 assert(s);
 assert(s->buffer);
 assert(s->top > 0);

 unsigned char* ptr = (unsigned char*)s->buffer;
 s->top--;
 ptr += s->item_length * s->top;
 return ptr;
}
# 254 "./a1.c"
void tokenizer_test_fixture(void);

void all_unit_tests(void)
{
 tokenizer_test_fixture();
}

int main(int argc, char* argv[])
{
 run_tests(all_unit_tests);
 return 0;
}
# 288 "./a1.c"
unsigned int GetTickCount() { return 0;}


static int sea_tests_run = 0;
static int sea_tests_passed = 0;
static int sea_tests_failed = 0;
static char* seatest_current_fixture;

static void (*seatest_fixture_setup)( void ) = 0;
static void (*seatest_fixture_teardown)( void ) = 0;

void fixture_setup(void (*setup)( void ))
{
 seatest_fixture_setup = setup;
}
void fixture_teardown(void (*teardown)( void ))
{
 seatest_fixture_teardown = teardown;
}

void seatest_setup()
{
 if(seatest_fixture_setup != 0) seatest_fixture_setup();
}

void seatest_teardown()
{
 if(seatest_fixture_teardown != 0) seatest_fixture_teardown();
}

char* test_file_name(char* path)
{
 char* file = path + strlen(path);
 while(file != path && *file!= '\\' ) file--;
 if(*file == '\\') file++;
 return file;
}

static int seatest_fixture_tests_run;
static int seatest_fixture_tests_failed;

void seatest_simple_test_result(int passed, char* reason, const char* function, unsigned int line)
{
 if (!passed)
 {
  __CPROVER_printf("%-20s Line %-5d %s\r\n", function, line, reason );
  sea_tests_failed++;
 }
 else
 {
  sea_tests_passed++;
 }
}

void seatest_assert_true(int test, const char* function, unsigned int line)
{
 seatest_simple_test_result(test, "Should of been true", function, line);

}

void seatest_assert_false(int test, const char* function, unsigned int line)
{
 seatest_simple_test_result(!test, "Should of been false", function, line);
}


void seatest_assert_int_equal(int expected, int actual, const char* function, unsigned int line)
{
 char s[100];
 sprintf(s, "Expected %d but was %d", expected, actual);
 seatest_simple_test_result(expected==actual, s, function, line);
}

void seatest_assert_float_equal( float expected, float actual, float delta, const char* function, unsigned int line )
{
 char s[100];
 float result = expected-actual;
 sprintf(s, "Expected %f but was %f", expected, actual);
 if(result < 0.0) result = 0.0 - result;
 seatest_simple_test_result( result <= delta, s, function, line);
}

void seatest_assert_double_equal( double expected, double actual, double delta, const char* function, unsigned int line )
{
 char s[100];
 double result = expected-actual;
 sprintf(s, "Expected %f but was %f", expected, actual);
 if(result < 0.0) result = 0.0 - result;
 seatest_simple_test_result( result <= delta, s, function, line);
}

void seatest_assert_string_equal(char* expected, char* actual, const char* function, unsigned int line)
{
 char s[100];
 sprintf(s, "Expected %s but was %s", expected, actual);
 seatest_simple_test_result(strcmp(expected, actual)==0, s, function, line);
}

void seatest_assert_string_ends_with(char* expected, char* actual, const char* function, unsigned int line)
{
 char s[100];
 sprintf(s, "Expected %s to end with %s", actual, expected);
 seatest_simple_test_result(strcmp(expected, actual+(strlen(actual)-strlen(expected)))==0, s, function, line);
}

void seatest_assert_string_starts_with(char* expected, char* actual, const char* function, unsigned int line)
{
 char s[100];
 sprintf(s, "Expected %s to start with %s", actual, expected);
 seatest_simple_test_result(strncmp(expected, actual, strlen(expected))==0, s, function, line);
}

void seatest_assert_string_contains(char* expected, char* actual, const char* function, unsigned int line)
{
 char s[100];
 sprintf(s, "Expected %s to be in %s", expected, actual);
 seatest_simple_test_result(strstr(expected, actual)!=0, s, function, line);
}

void seatest_assert_string_doesnt_contain(char* expected, char* actual, const char* function, unsigned int line)
{
 char s[100];
 sprintf(s, "Expected %s not to have %s in it", actual, expected);
 seatest_simple_test_result(strstr(expected, actual)==0, s, function, line);
}

void seatest_run_test(void)
{
 sea_tests_run++;
}

void seatest_header_printer(char* s, int length, char f)
{
 int l = strlen(s);
 int d = (length- (l + 2)) / 2;
 int i;
 for(i = 0; i<d; i++) __CPROVER_printf("%c",f);
 __CPROVER_printf(" %s ", s);
 for(i = (d+l+2); i<length; i++) __CPROVER_printf("%c",f);
 __CPROVER_printf("\r\n");
}


void seatest_test_fixture_start(char* filepath)
{
 seatest_current_fixture = test_file_name(filepath);
 seatest_header_printer(seatest_current_fixture, 50, '-');
 seatest_fixture_tests_failed = sea_tests_failed;
 seatest_fixture_tests_run = sea_tests_run;
 seatest_fixture_teardown = 0;
 seatest_fixture_setup = 0;
}

void seatest_test_fixture_end()
{
 char s[100];
 sprintf(s, "%d run  %d failed", sea_tests_run-seatest_fixture_tests_run, sea_tests_failed-seatest_fixture_tests_failed);
 seatest_header_printer(s, 50, ' ');
 __CPROVER_printf("\r\n");
}

static char* seatest_fixture_filter = 0;
static char* seatest_test_filter = 0;

void fixture_filter(char* filter)
{
 seatest_fixture_filter = filter;
}


void test_filter(char* filter)
{
 seatest_test_filter = filter;
}


int seatest_should_run( char* fixture, char* test)
{
 int run = 1;
 if(seatest_fixture_filter)
 {
  if(strncmp(seatest_fixture_filter, fixture, strlen(seatest_fixture_filter)) != 0) run = 0;
 }
 if(seatest_test_filter)
 {
  if(strncmp(seatest_test_filter, test, strlen(seatest_test_filter)) != 0) run = 0;
 }
 return run;
}

int run_tests(void (*tests)(void))
{
 unsigned long end;
 unsigned long start = GetTickCount();
 tests();
 end = GetTickCount();
 __CPROVER_printf("\r\n\r\n==================================================\r\n");
 if (sea_tests_failed > 0) {
  __CPROVER_printf("                      Failed\r\n");
 }
 else {
  __CPROVER_printf("               ALL TESTS PASSED\r\n");
 }
 __CPROVER_printf("                 %d tests run\r\n", sea_tests_run);
 __CPROVER_printf("                    in %d ms\r\n",end - start);
 __CPROVER_printf("==================================================\r\n");

 getchar();
 return sea_tests_failed == 0;
}
# 521 "./a1.c"
static int is_whitespace(char c)
{
 return ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'));
}

static int is_alpha(char c)
{
 if (c < 0)
 {
  return 1;
 }
 return (((c >= 'a') && (c <= 'z')) ||
         ((c >= 'A') && (c <= 'Z')) ||
         (c == '_'));
}

static int is_alphanum(char c)
{
 return (is_alpha(c) || isdigit(c));
}

static int is_digit(char c)
{
 return ((c >= '0') && (c <= '9'));
}

static struct {
 char* str;
 enum token_type token_type;
} keywords[] = {
 {"and", TT_OP_AND},
 {"or", TT_OP_OR},
};

void init_tokenizer(struct tokenizer* t, char* source)
{
 t->source = (char*)malloc(strlen(source) + 1);
 strcpy(t->source, source);
 t->source_index = 0;
 t->index_stack = create_stack(sizeof(int));
 t->token_value = ((void *)0);
 t->token_type = TT_NONE;
 t->line_number = 1;
}

void release_tokenizer(struct tokenizer* t)
{
 free(t->source);
 free(t->token_value);
 destroy_stack(t->index_stack);
 memset(t, 0, sizeof(struct tokenizer));
}

static void eatwhitespace(struct tokenizer* t)
{
eatwhitespace_begin:

 while (is_whitespace(t->source[t->source_index])) {
  if ('\n' == t->source[t->source_index]) {
   t->line_number++;
  }
  t->source_index++;
 }


 if (t->source[t->source_index] == '#') {
  while (t->source[t->source_index] != '\n') {



   if (t->source[t->source_index] == '\0') {
    break;
   }
   t->source_index++;
  }
  goto eatwhitespace_begin;
 }


 if (('/' == t->source[t->source_index]) &&
     ('*' == t->source[t->source_index+1])) {
  t->source_index += 2;
  while (t->source[t->source_index] != '\0') {
   if (('*' == t->source[t->source_index]) &&
       ('/' == t->source[t->source_index+1])) {
    t->source_index += 2;
    break;
   }
   t->source_index++;
  }
  goto eatwhitespace_begin;
 }

}


static void tokenize_number(struct tokenizer* t)
{
 t->token_type == TT_NUMBER;
 t->token_value = malloc(sizeof(int));
 (*(int*)(t->token_value)) = t->source[t->source_index++] - '0';
 while (is_digit(t->source[t->source_index])) {
  (*(int*)(t->token_value)) *= 10;
  (*(int*)(t->token_value)) += t->source[t->source_index] - '0';
 }
}

static void tokenize_identifier(struct tokenizer* t)
{
 int i = 0;

 t->token_value = (char*)malloc(64);
 ((char*)(t->token_value))[i++] = t->source[t->source_index++];
 while (is_alphanum( t->source[t->source_index])) {
  ((char*)(t->token_value))[i++] = t->source[t->source_index++];
  if (64 == i) {
   fprintf(stderr, "MAX_IDENT_LENGTH reached :%d\n", t->line_number);
   exit(1);
  }
 }
 ((char*)(t->token_value))[i] = '\0';
 for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
  if (strcmp(((char*)(t->token_value)), keywords[i].str) == 0) {
   t->token_type = keywords[i].token_type;
   return;
  }
 }
 t->token_type = TT_IDENT;
}

static void tokenize_string(struct tokenizer* t)
{
 int i = 0;

 t->token_value = malloc(1024);
 t->source_index++;
 while (t->source[t->source_index] != '"') {
  if (t->source[t->source_index] == '\\') {
   if (t->source[t->source_index+1] == 'n') {
    ((char*)(t->token_value))[i++] = '\n';
    t->source_index += 2;
   }
   else if (t->source[t->source_index+1] == '"') {
    ((char*)(t->token_value))[i++] = '\"';
    t->source_index += 2;
   }
   else if (t->source[t->source_index+1] == '\\') {
    ((char*)(t->token_value))[i++] = '\\';
    t->source_index += 2;
   }
   else {
    ((char*)(t->token_value))[i++] = '\\';
    t->source_index++;
   }
  }
  else {
   ((char*)(t->token_value))[i++] = t->source[t->source_index++];
  }
  if (i >= 1024) {
   fprintf(stderr, "max inline string length reached\n");
   exit(1);
  }
 }
 ((char*)(t->token_value))[i] = '\0';
 t->source_index++;
 t->token_type = TT_STRING;
}

enum token_type get_token(struct tokenizer* t)
{
 if (t->token_value) {
  free(t->token_value);
  t->token_value = ((void *)0);
 }

 eatwhitespace(t);

 stack_push(t->index_stack, &t->source_index);

 if ('\0' == t->source[t->source_index]) {
  t->token_type = TT_EOF;
  return TT_EOF;
 }

 if (is_digit(t->source[t->source_index])) {
  tokenize_number(t);
  return TT_NUMBER;
 }

 if (is_alpha(t->source[t->source_index])) {
  tokenize_identifier(t);
  return TT_IDENT;
 }

 if ('"' == t->source[t->source_index]) {
  tokenize_string(t);
  return TT_STRING;
 }

 return TT_UNKNOWN;
}

void unget_token(struct tokenizer* t)
{
 int prev_source_index = *(int*)stack_pop(t->index_stack);
 if (t->source_index <= prev_source_index) {
  t->source_index = prev_source_index;
  return;
 }
 do {
  t->source_index--;
  if ('\n' == t->source[t->source_index]) {
   t->line_number--;
  }
 } while (t->source_index > prev_source_index);
}


static void tokenizer_test1()
{
 struct tokenizer* t = (struct tokenizer*)malloc(sizeof(struct tokenizer));
 init_tokenizer(t, " 1 \"asd\" 3");
 do { seatest_assert_int_equal(TT_NUMBER, get_token(t), "<unknown>", 743); } while (0);
 do { seatest_assert_int_equal(TT_STRING, get_token(t), "<unknown>", 744); } while (0);
 do { seatest_assert_int_equal(TT_NUMBER, get_token(t), "<unknown>", 745); } while (0);
 unget_token(t);
 unget_token(t);
 unget_token(t);
 do { seatest_assert_int_equal(TT_NUMBER, get_token(t), "<unknown>", 749); } while (0);
 do { seatest_assert_int_equal(TT_STRING, get_token(t), "<unknown>", 750); } while (0);
 do { seatest_assert_int_equal(TT_NUMBER, get_token(t), "<unknown>", 751); } while (0);
 release_tokenizer(t);
 free(t);
}

void tokenizer_test_fixture(void)
{
 do { seatest_test_fixture_start("./a1.c"); } while (0);
 do { if(seatest_should_run("./a1.c", "tokenizer_test1")) {seatest_setup(); tokenizer_test1(); seatest_teardown(); seatest_run_test(); }} while (0);
 do { seatest_test_fixture_end();} while (0);
}
