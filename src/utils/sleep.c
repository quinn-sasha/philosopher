#include "philo.h"
#include "utils.h"

void usleep_until(t_timeval end) {
  t_timeval now;
  while (true) {
    gettimeofday(&now, NULL);
    suseconds_t diff = timediff_usec(now, end);
    if (diff <= 0)
      return;
    usleep(useconds_t(diff / 2));
  }
}

void usleep_since(t_timeval start, int length_ms) {
  t_timeval end = timeadd_msec(start, length_ms);
  usleep_until(end);
}
