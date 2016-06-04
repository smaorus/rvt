#ifndef __ANSI_C_FCNTL_H
#define __ANSI_C_FCNTL_H

#include <sys/types.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define O_ACCMODE          0003
#define O_RDONLY             00
#define O_WRONLY             01
#define O_RDWR               02
#define O_CREAT            0100 /* not fcntl */
#define O_EXCL             0200 /* not fcntl */
#define O_NOCTTY           0400 /* not fcntl */
#define O_TRUNC           01000 /* not fcntl */
#define O_APPEND          02000
#define O_NONBLOCK        04000
#define O_NDELAY        O_NONBLOCK
#define O_SYNC           010000
#define O_FSYNC          O_SYNC
#define O_ASYNC          020000
#define O_LARGEFULE           0
#define O_DIRECTORY           0
#define O_NOFOLLOW            0

#define F_DUPFD         0       /* Duplicate file descriptor.  */
#define F_GETFD         1       /* Get file descriptor flags.  */
#define F_SETFD         2       /* Set file descriptor flags.  */
#define F_GETFL         3       /* Get file status flags.  */
#define F_SETFL         4       /* Set file status flags.  */
#define F_GETLK         5       /* Get record locking info.  */
#define F_SETLK         6       /* Set record locking info (non-blocking).  */
#define F_SETLKW        7       /* Set record locking info (blocking).  */
#define F_GETLK64       12      /* Get record locking info.  */
#define F_SETLK64       13      /* Set record locking info (non-blocking).  */
#define F_SETLKW64      14      /* Set record locking info (blocking).  */

#define FD_CLOEXEC      1       /* actually anything with low bit set goes */

#define F_RDLCK         0       /* Read lock.  */
#define F_WRLCK         1       /* Write lock.  */
#define F_UNLCK         2       /* Remove lock.  */

#define F_EXLCK         4       /* or 3 */
#define F_SHLCK         8       /* or 4 */

struct flock
{
  short int l_type;
  short int l_whence;
  off_t l_start;
  off_t l_len;
  pid_t l_pid;
};
  
extern int fcntl (int __fd, int __cmd, ...);
extern int open (const char *__file, int __oflag, ...);
extern int creat (const char *__file, mode_t __mode);
extern int lockf (int __fd, int __cmd, off_t __len);

#ifdef  __cplusplus
}
#endif
                                   
#endif



