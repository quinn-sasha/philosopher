#include "philo.h"
#include "simulation.h"
#include "utils.h"

/*
* It is unsafe since it accesses last_eat_at without philo's mutex.
* Return true if someone dies, otherwise false.
*/
bool unsafe_write_log(t_philo *philo, const char *message, t_timeval *tp) {
  bool is_end;
  t_timeval now;
  ptrhead_mutex_lock(&philo->data->monitor.mutex);
  if (philo->data->monitor.is_dead)
    is_end = true;
  else
  {
    is_end = unsafe_is_dead(*philo, &now);
    if (is_end)
      unsafe_write_dead_log(philo, now);
    else
    {
      int timestamp_ms = timediff_msec(philo->data->started_at, now);
      printf("%d %d %s\n", timestamp_ms, philo->id, message);
    }
    if (tp != NULL)
      *tp = now;
  }
  pthread_mutex_unlock(&philo->data->monitor.mutex);
  return is_end;
}

// It needs mutex for printed_dead_log and monitor.is_dead to write them
// 死亡ログは一度しか表示されない
static void unsafe_write_dead_log(t_philo *philo, t_timeval died_at) {
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
