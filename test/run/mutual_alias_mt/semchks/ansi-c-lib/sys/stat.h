#ifndef __ANSI_C_STAT_H
#define __ANSI_C_STAT_H

#include <time.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct stat {
    //dev_t         st_dev;      /* device */
    //ino_t         st_ino;      /* inode */
    //mode_t        st_mode;     /* protection */
    unsigned      st_nlink;    /* number of hard links */
    //uid_t         st_uid;      /* user ID of owner */
    //gid_t         st_gid;      /* group ID of owner */
    //dev_t         st_rdev;     /* device type (if inode device) */
    unsigned long st_size;     /* total size, in bytes */
    unsigned long st_blksize;  /* blocksize for filesystem I/O */
    unsigned long st_blocks;   /* number of blocks allocated */
    time_t        st_atime;    /* time of last access */
    time_t        st_mtime;    /* time of last modification */
    time_t        st_ctime;    /* time of last change */
};

int stat(const char *file_name, struct stat *buf);
int fstat(int filedes, struct stat *buf);
int lstat(const char *file_name, struct stat *buf);

#ifdef  __cplusplus
}
#endif

#endif
