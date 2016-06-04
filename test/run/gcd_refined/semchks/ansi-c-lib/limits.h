#ifndef __ANSI_C_LIMITS_H
#define __ANSI_C_LIMITS_H

#if __WORDSIZE == 16
#define INT_MIN (-INT_MAX-1)
#define INT_MAX 32767
#define UINT_MAX 65535
#else
#if __WORDSIZE == 32
#define INT_MIN (-INT_MAX-1)
#define INT_MAX 2147483647
#define UINT_MAX 4294967295U
#else
#if __WORDSIZE == 64
#define INT_MIN (-INT_MAX-1)
#define INT_MAX 2147483647
#define UINT_MAX 4294967295U
#else
#error unknown word size
#endif
#endif
#endif

#endif
