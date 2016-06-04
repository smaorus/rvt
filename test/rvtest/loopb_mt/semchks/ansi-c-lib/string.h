#ifndef __ANSI_C_STRING_H
#define __ANSI_C_STRING_H

#include <sys/types.h>

#ifdef  __cplusplus
extern "C" {
#endif
  
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

#ifdef  __cplusplus
}
#endif

#endif


