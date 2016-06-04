#ifndef __ANSI_C_STDLIB_H
#define __ANSI_C_STDLIB_H

#include <sys/types.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

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

#define RAND_MAX (0x7fffffff)

/* We define these the same for all machines.
   Changes from this to the outside world should be done in `_exit'.  */
#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */

#ifdef  __cplusplus
}
#endif
                                                 
#endif
