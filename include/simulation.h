#ifndef SIMULATION_H
#define SIMULATION_H

// moniotr.c
#define MONITOR_INTERVAL_IN_USEC 1000
void *monitor_thread(void *arg);

// philosopher.c
void *philosopher_thread(void *arg);

// unsafe_functions.c
bool unsafe_is_hungry(t_philo philo);
bool unsafe_is_dead(t_philo philo, t_timeval *checked_at);

// log.c
void write_dead_log(t_philo *philo, t_timeval died_at);
bool unsafe_write_log(t_philo *philo, const char *message, t_timeval *tp);

// simulation.c
void start_simulation(t_data *data);
void wait_simulation_ends(t_data data);

#endif
