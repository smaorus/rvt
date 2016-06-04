/* Headers for predefined outlined functions */
float rv_mult(float x, float y);
float rv_div(float x, float y);
int rv_mod (int x, int y);
# 1 "./mutual.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./mutual.c"
# 1 "/cygdrive/c/NewRVT/Debug/../tools/scripts/../ansi-c-lib/stdio.h" 1



# 1 "/cygdrive/c/NewRVT/Debug/../tools/scripts/../ansi-c-lib/sys/types.h" 1



typedef int pid_t;
typedef unsigned int size_t;
typedef unsigned char u_char;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;

typedef unsigned int off_t;
typedef unsigned int mode_t;
# 25 "/cygdrive/c/NewRVT/Debug/../tools/scripts/../ansi-c-lib/sys/types.h"
typedef unsigned int u_int;

typedef int uid_t;
# 5 "/cygdrive/c/NewRVT/Debug/../tools/scripts/../ansi-c-lib/stdio.h" 2





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
# 38 "/cygdrive/c/NewRVT/Debug/../tools/scripts/../ansi-c-lib/stdio.h"
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
# 2 "./mutual.c" 2

int F(int n);
int M(int n);
int F(int n){
 if ( n==0 ) return 1;
 return n - M(F(n-1));
}

int M(int n) {
 if ( n == 0 ) return 0;
 return n - F(M(n-1));
}

int main(){
 int i, l = 0;
 for(i=0; i < 20; i++) {
  __CPROVER_printf("%2d ", F(i));
  l++;
  if (i > 20) return 3;
 }
 __CPROVER_printf("\n");
 for(i=0; i < 20; i++) {
  __CPROVER_printf("%2d ", M(i));
  l++;
 }
 __CPROVER_printf("\n");
 return l;
}
