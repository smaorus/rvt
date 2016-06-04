#ifndef __ANSI_C_UTIME_H
#define __ANSI_C_UTIME_H

// pow and related

#ifdef  __cplusplus
extern "C" {
#endif

struct utimbuf {
        time_t actime;  /* access time */
        time_t modtime; /* modification time */
};

int utime(const char *filename, const struct utimbuf *buf);
int utimes(const char *filename, const struct timeval tv[2]);

#ifdef  __cplusplus
}
#endif

#endif


