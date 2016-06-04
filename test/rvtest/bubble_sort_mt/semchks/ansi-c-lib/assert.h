#ifndef __ANSI_C_ASSERT_H
#define __ANSI_C_ASSERT_H

#ifdef  __cplusplus
extern "C" void assert(bool c);
#else
void assert(_Bool c);
#endif

#endif
