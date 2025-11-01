#ifndef UTILS_H
#define UTILS_H

// time.c

#define MSEC_IN_USEC 1000
#define SEC_IN_MSEC 1000
#define SEC_IN_USEC 1000000

t_timeval timeadd_msec(t_timeval t, int offset_ms);

#endif
