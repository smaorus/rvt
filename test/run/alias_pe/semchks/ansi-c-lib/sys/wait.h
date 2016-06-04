#ifndef __ANSI_C_WAIT_H
#define __ANSI_C_WAIT_H

#include <signal.h>

#ifdef  __cplusplus
extern "C" {
#endif

#include "types.h"

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

#define WIFEXITED(status)   0
#define WEXITSTATUS(status) 0
#define WIFSIGNALED(status) 0
#define WTERMSIG(status)    0
#define WIFSTOPPED(status)  0
#define WSTOPSIG(status)    0

#ifdef  __cplusplus
}
#endif

#endif
