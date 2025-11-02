#include "philo.h"
#include "simulation.h"
#include "utils.h"

// Monitor needs philosopher's mutex to access each eat_count and last_eat_at
// 終了条件: 誰か一人でも死ぬ、もしくは全員が max_eat 回数食事する
static bool should_continue_simulation(t_data *data) {
  t_timeval checked_at;
  bool is_dead_any = false;
  bool is_eating = false;
  int i = 0;
  while (!is_dead_any && i < data->args.num_philo) {
    pthread_mutex_lock(&data->philosophers[i].mutex);
    if (unsafe_is_hungry(data->philosophers[i])) {
      is_eating = true;
      if (unsafe_is_dead(data->philosophers[i], &checked_at)) {
        write_dead_log(&data->philosophers[i], checked_at);
        is_dead_any = true;
      }
    }
    pthread_mutex_unlock(&data->philosophers[i].mutex);
    i++;
  }
  return (!is_dead_any && is_eating);
}

void *monitor_thread(void *arg) {
  t_data *data = (t_data *)arg;
  usleep_until(data->started_at);
  while (true) {
    usleep(MONITOR_INTERVAL_IN_USEC);
    if (!should_continue_simulation(data))
      return;
  }
}
