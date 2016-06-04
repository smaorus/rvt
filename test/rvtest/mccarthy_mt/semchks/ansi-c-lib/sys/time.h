#ifndef __ANSI_C_TIME_H
#define __ANSI_C_TIME_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef int time_t;

time_t time(time_t *t);

struct tm
 {
  int     tm_sec;         /* seconds */
  int     tm_min;         /* minutes */
  int     tm_hour;        /* hours */
  int     tm_mday;        /* day of the month */
  int     tm_mon;         /* month */
  int     tm_year;        /* year */
  int     tm_wday;        /* day of the week */
  int     tm_yday;        /* day in the year */
  int     tm_isdst;       /* daylight saving time */
 };

char *asctime(const struct tm *timeptr);
char *ctime(const time_t *timep);
struct tm *gmtime(const time_t *timep);
struct tm *localtime(const time_t *timep);
time_t mktime(struct tm *timeptr);
unsigned strftime(char *s, unsigned max, const char *format,
                  const struct tm *tm);
extern char *tzname[2];
extern int daylight;

// extern long int timezone;
struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

struct timeval
{
  unsigned tv_sec;
  unsigned tv_usec;
};

int gettimeofday(struct timeval *, struct timezone *);

#ifdef  __cplusplus
}
#endif

#endif
