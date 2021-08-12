#ifndef APP_TIME_H_
#define APP_TIME_H_

#include <stdio.h> /* Define size_t */
#include <stdint.h>

#define CLOCKS_PER_SEC 1000000000L

#define CLOCK_REALTIME 0

typedef long clock_t;


typedef uint32_t  time_t;         /* Holds time in seconds */
typedef uint8_t   clockid_t;   

struct timespec {
        time_t   tv_sec;        /* seconds */
        long     tv_nsec;       /* nanoseconds */
};


clock_t clock(void);

int clock_gettime(clockid_t clk_id, struct timespec *tp);

#endif
