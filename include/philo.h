#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>      // printf
#include <stdlib.h>     // malloc, free
#include <string.h>     // memset
#include <unistd.h>     // write, usleep
#include <sys/time.h>   // gettimeofday
#include <pthread.h>    // pthread_create, pthread_detach, pthread_join,
                        // pthread_mutex_init, pthread_mutex_destroy,
                        // pthread_mutex_lock, pthread_mutex_unlock
#include <stdbool.h>
#include "libftsubset.h"
#include "parse_argument.h"
#include "utils.h"

void init_data(t_data *data);

typedef struct timeval t_timeval;
typedef struct s_data t_data;
typedef struct s_args t_args;
typedef struct s_philo t_philo;
typedef struct s_fork t_fork;
typedef struct s_monitor t_monitor;

/*
* 1 <= num_philo < MAX_PHILO
* 0 <= time_to_die_ms
* 0 <= time_to_eat_ms
* 0 <= time_to_sleep_ms
* 1 <= max_eat
*/
struct s_args {
  int num_philo;
  int time_to_die_ms;
  int time_to_eat_ms;
  int time_to_sleep_ms;
  int max_eat;
};

struct s_monitor {
  pthread_t tid;
  pthread_mutex_t mutex;
  bool is_dead;
};

struct s_fork {
  pthread_mutex_t mutex;
  int id;
};

/*
* eat_count and last_eat_at: They need mutex because monitor reads, and philo writes them
* next_eat_at: private to a philosopher
* last_sleep_at: private to a philosopher
*/
struct s_philo {
  pthread_t tid;
  int id;
  pthread_mutex_t mutex;
  int eat_count;
  t_timeval last_eat_at;
  t_timeval next_eat_at;
  t_timeval last_sleep_at;
  t_fork *first;
  t_fork *second;
  t_data *data;
};

struct s_data {
  t_timeval started_at;
  int optimal_interval_ms;
  t_args args;
  t_monitor monitor;
  t_fork forks[MAX_PHILO];
  t_philo philosophers[MAX_PHILO];
};

#endif
