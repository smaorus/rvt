#ifndef __ANSI_C_RESOURCE_H
#define __ANSI_C_RESOURCE_H

#include <sys/time.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct rlimit {
    long rlim_cur;   /* Soft limit */
    long rlim_max;   /* Hard limit (ceiling for rlim_cur) */
};

struct rusage {
    struct timeval ru_utime; /* user time used */
    struct timeval ru_stime; /* system time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims */
    long   ru_majflt;        /* page faults */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* messages sent */
    long   ru_msgrcv;        /* messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
};

int getrlimit(int resource, struct rlimit *rlim);
int getrusage(int who, struct rusage *usage);
int setrlimit(int resource, const struct rlimit *rlim);

#define RLIMIT_AS 0
#define RLIMIT_CORE 1

#define RUSAGE_SELF 0
#define RUSAGE_CHILDREN 1

#ifdef  __cplusplus
}
#endif

#endif
