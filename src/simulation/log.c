#include "philo.h"
#include "utils.h"

// It needs mutex for printed_dead_log and monitor.is_dead to write them
void unsafe_write_dead_log(t_philo *philo, t_timeval died_at) {
  static bool printed_dead_log = false;
  if (printed_dead_log)
    return;
  philo->data->monitor.is_dead = true;
  int timestamp_ms = timediff_msec(philo->data->started_at, died_at);
  printf("%d %d died\n", timestamp_ms ,philo->id);
  printed_dead_log = true;
}

void write_dead_log(t_philo *philo, t_timeval died_at) {
  pthread_mutex_lock(&philo->data->monitor.mutex);
  unsafe_write_dead_log(philo, died_at);
  pthread_mutex_unlock(&philo->data->monitor.mutex);
}
