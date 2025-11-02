#include "philo.h"
#include "simulation.h"

static void create_monitor_thread(t_data *data) {
  pthread_mutex_init(&data->monitor.mutex, NULL);
  pthread_create(&data->monitor.tid, NULL, monitor_thread, data);
}

static void create_philosophers_thread(t_philo *philo) {
  const int num_philo = philo->data->args.num_philo;
  int i = 0;
  while (i < num_philo) {
    pthread_create(&philo[i].tid, NULL, philosopher_thread, &philo[i]);
    i++;
  }
}

void start_simulation(t_data *data) {
  create_monitor_thread(data);
  create_philosophers_thread(data->philosophers);
}

