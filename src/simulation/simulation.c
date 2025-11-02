#include "philo.h"
#include "simulation.h"

static void create_monitor_thread(t_data *data) {
  pthread_mutex_init(&data->monitor.mutex, NULL);
  pthread_create(&data->monitor.tid, NULL, monitor_thread, data);
}

static void create_philosophers_thread() {

}

void start_simulation(t_data *data) {
  create_monitor_thread(data);
  create_philosophers_thread();
}

