#ifndef __ANSI_C_STDIO_H
#define __ANSI_C_STDIO_H

#include <sys/types.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct __FILE
{
  int flags;
};

#define SEEK_SET        0       /* Seek from beginning of file.  */
#define SEEK_CUR        1       /* Seek from current position.  */
#define SEEK_END        2       /* Seek from end of file.  */

typedef struct __FILE FILE;

int fflush(FILE *stream);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int __CPROVER_printf(const char *format, ...);

//#define printf( format, args... ) __CPROVER_printf( format, ## args)
#define printf __CPROVER_printf

//extern int printf(const char *format, ...)
//{
//  __CPROVER_HIDE:
//  __CPROVER_printf(format);
//}

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

#define EOF (-1)

#ifdef  __cplusplus
}
#endif
                                                                                                                        
#endif

