#include "philo.h"
#include "utils.h"

static void init_forks(t_fork *forks, const int num_forks) {
  int i = 0;
  while (i < num_forks) {
    forks[i].id = i + 1;
    pthread_mutex_init(&forks[i].mutex, NULL);
    i++;
  }
}

static void init_philosophers(t_data *data) {
  const int num_philos = data->args.num_philo;
  memset(data->philosophers, 0, sizeof(t_philo) * MAX_PHILO);
  int i = 0;
  while (i < num_philos) {
    t_philo *philo = &data->philosophers[i];
    philo->id = i + 1;
    philo->state = PH_SLEEPING;
    philo->eat_count = 0;
    philo->last_eat_at = data->started_at;
    philo->next_eat_at = calculate_initial_eat_at(philo->id, data);
    philo->last_sleep_at = data->started_at;
    pthread_mutex_init(&philo->mutex, NULL);
    if (i == num_philos - 1) {
      philo->first = &data->forks[0];
      philo->second = &data->forks[i];
    } else {
      philo->first = &data->forks[i];
      philo->second = &data->forks[i + 1];
    }
    philo->data = data;
    i++;
  }
}

/*
n = 2k or n = 2k + 1
k = n / 2 (同時に食事をできる哲学者数)
optimal interval = time_to_eat * (n / k)
n / k ≒ 2 (or 3)
optimal interval = time_to_eat * 2(or 3) (２つのグループが両方とも食事を終えるまでにかかる最低限の時間)
*/
static int calculate_optimal_interval_ms(t_args *args) {
  const int n = args->num_philo;
  const int k = args->num_philo / 2;
  const int min_interval_ms = args->time_to_eat_ms + args->time_to_sleep_ms;

  if (n == 1)
    return min_interval_ms;
  int result = args->time_to_eat_ms * (n / k);
  if (result < min_interval_ms)
    return min_interval_ms;
  return result;
}

/*
* start_position: 各哲学者の開始時刻をIDに基づいて順位付けする
* time_to_eat / k: 同じグループに属するk人の哲学者が time_to_eat 間で食事を始められるようにするためにずらす時間
* start_offset_ms = 一人分のズレ幅 * 自分のスタートする順位
*/
static t_timeval calculate_initial_eat_at(int philo_id, t_data *data) {
  const int n = data->args.num_philo;
  const int k = n / 2;
  if (n == 1)
    return data->started_at;
  const int start_postion = (k * philo_id) % n;
  const int start_offset_ms = (data->args.time_to_eat_ms / k) * start_postion;
  return timeadd_msec(data->started_at, start_offset_ms);
}

// started_at を現在の1秒後に設定して、全スレッドを同時に開始させる
void init_data(t_data *data) {
  gettimeofday(&data->started_at, NULL);
  data->started_at.tv_sec += 1;
  data->started_at.tv_usec = 0;
  data->optimal_interval_ms = calculate_optimal_interval_ms(&data->args);
  init_forks(data->forks, data->args.num_philo);
  init_philosophers(data);
}

