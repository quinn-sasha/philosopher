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
