#include "philo.h"
#include "utils.h"

/*
t.tv_usec += offset_ms * MSEC_IN_USEC;
というコードは offset_ms が INT_MAX に近い時にオーバーフローが起こる可能性がある
*/
t_timeval timeadd_msec(t_timeval t, int offset_ms) {
  const int offset_only_ms = offset_ms % SEC_IN_MSEC;
  t.tv_usec += offset_only_ms * MSEC_IN_USEC;
  t.tv_sec += offset_ms / SEC_IN_MSEC;
  t.tv_sec += t.tv_usec / SEC_IN_USEC;
  t.tv_usec %= SEC_IN_USEC;
  return t;
}

int timediff_msec(t_timeval start, t_timeval end) {
  int diff = 0;
  diff += (int)(end.tv_sec - start.tv_sec) * SEC_IN_MSEC;
  diff += (end.tv_usec - start.tv_usec) / MSEC_IN_USEC;
  return diff;
}

suseconds_t timediff_usec(t_timeval start, t_timeval end) {
  suseconds_t diff = 0;
  diff += (suseconds_t)(end.tv_sec - start.tv_sec) * SEC_IN_USEC;
  diff += end.tv_usec - start.tv_usec;
  return diff;
}

void rounddown_msec(t_timeval *tp) {
  tp->tv_usec /= MSEC_IN_USEC;
  tp->tv_usec *= MSEC_IN_USEC;
}
