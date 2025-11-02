#include "philo.h"
#include "utils.h"

bool unsafe_is_hungry(t_philo philo) {
  const int max_eat = philo.data->args.max_eat;
  if (max_eat < 0)
    return true;
  return philo.eat_count < max_eat;
}

bool unsafe_is_dead(t_philo philo, t_timeval *checked_at) {
  t_timeval now;
  gettimeofday(&now, NULL);
  rounddown_msec(&now);
  if (checked_at != NULL)
    *checked_at = now;
  const int time_to_die_ms = philo.data->args.time_to_die_ms;
  t_timeval deadline = timeadd_msec(philo.last_eat_at, time_to_die_ms);
  suseconds_t diff = timediff_usec(now, deadline);
  if (diff < 0)
    return true;
  return false;
}
