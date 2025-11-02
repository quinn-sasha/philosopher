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
