#ifndef __ANSI_C_UNISTD_H
#define __ANSI_C_UNISTD_H

#include <sys/types.h>
#include <sys/fcntl.h>

#ifdef  __cplusplus
extern "C" {
#endif

unsigned int sleep(unsigned int seconds);

int chdir(const char *path);
int fchdir(int fd);

long int read(int fd, void *buf, unsigned long count);
long int write(int fd, const void *buf, unsigned long count);
//int open(const char *pathname, int flags, unsigned int mode);
//int open(const char *pathname, int flags);
//int creat(const char *pathname, unsigned int mode);
int close(int fd);
int unlink(const char *pathname);

#define R_OK    4               /* Test for read permission.  */
#define W_OK    2               /* Test for write permission.  */
#define X_OK    1               /* Test for execute permission.  */
#define F_OK    0               /* Test for existence.  */

/* Test for access to NAME using the real UID and real GID.  */
int access (const char *name, int type);

pid_t getpid(void);
pid_t getppid(void);

int getpagesize(void);

int isatty(int);
unsigned alarm(unsigned);
pid_t fork(void);

#ifdef  __cplusplus
}
#endif

#endif
