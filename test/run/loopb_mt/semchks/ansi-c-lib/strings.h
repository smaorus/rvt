#ifndef __ANSI_STRINGS_H
#define __ANSI_STRINGS_H      1

#ifdef  __cplusplus
extern "C" {
#endif
  
/* Set N bytes of S to 0.  */
void bzero (void *__s, size_t __n);

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
void bcopy (const void *__src, void *__dest, size_t __n);

/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
int ffs (int __i);

/* Find the first occurrence of C in S (same as strchr).  */
char *index (const char *__s, int __c);

/* Find the last occurrence of C in S (same as strrchr).  */
char *rindex (const char *__s, int __c);

/* Compare S1 and S2, ignoring case.  */
int strcasecmp (const char *__s1, __const char *__s2);

/* Compare no more than N chars of S1 and S2, ignoring case.  */
int strncasecmp (const char *__s1, __const char *__s2, size_t __n);

#ifdef  __cplusplus
}
#endif  

#endif /* strings.h */
