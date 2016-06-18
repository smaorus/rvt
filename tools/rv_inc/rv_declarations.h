_Bool __CPROVER_array_equal(void *, void *);
void __CPROVER_array_copy(void *, void *);
void __CPROVER_assert(_Bool, char*);
void assert(_Bool assertion) {__CPROVER_assert(assertion, "RVT assertion");}
void __CPROVER_assume(_Bool);
void assume(_Bool assumption) { __CPROVER_assume(assumption); }


_Bool nondet_Bool();
int nondet_int();
long nondet_long();

void* malloc(unsigned int);

/* Used for void * replacement with an array of bytes: */
#include <stddef.h>
void *memcpy(void *dest, const void *src, size_t n);
int memcmp(const char*, const char*, size_t);


/*  RVT style (method 1) array macros */
/*#define RVT_COPY_ARRAY(dst,src,sz) {int i; for(i=0;i<sz;i++) dst[i] = src[i];}
#define RVT_NONDET_ARRAY(dst,sz)  {int i; for(i=0;i<sz;i++) dst[i] = nondet_int();}
#define RVT_FETCH_ARRAY(dst,src,sz) {int i; for(i=0;i<sz;i++) dst[i] = src[i];}
#define RVT_COMP_ARRAY(equal,dst,src,sz) {int i; for(i=0;i<sz;i++) equal = equal && (dst[i] == src[i]);}
#define RVT_ASSUME_EQ_ARRAY(dst,src,sz) {int i; for(i=0;i<sz;i++) assume(dst[i] == src[i]);}
#define RVT_ASSERT_EQ_ARRAY(dst,src,sz) {int i; for(i=0;i<sz;i++) assert(dst[i] == src[i]);}
*/

#define RVT_COPY_ARRAY(dst,src,sz)       {__CPROVER_array_copy(dst,src);}
#define RVT_NONDET_ARRAY(dst,sz)         {int nondet_arr[sz]; __CPROVER_array_copy(dst,nondet_arr);}
#define RVT_FETCH_ARRAY(dst,src,sz)      {__CPROVER_array_copy(dst,src);}
#define RVT_COMP_ARRAY(equal,dst,src,sz) {equal = equal && __CPROVER_array_equal(dst,src);}
#define RVT_ASSUME_EQ_ARRAY(dst,src,sz)  {assume(__CPROVER_array_equal(dst,src));}
#define RVT_ASSERT_EQ_ARRAY(dst,src,sz)  {assert(__CPROVER_array_equal(dst,src));}
// to declare infinite array: int A [__CPROVER_constant_infinity_uint
