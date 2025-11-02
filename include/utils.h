#ifndef UTILS_H
#define UTILS_H

// time.c

#define MSEC_IN_USEC 1000
#define SEC_IN_MSEC 1000
#define SEC_IN_USEC 1000000

t_timeval timeadd_msec(t_timeval t, int offset_ms);
int timediff_usec(t_timeval start, t_timeval end);
void rounddown_msec(t_timeval *tp);

#endif
