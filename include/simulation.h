#ifndef SIMULATION_H
#define SIMULATION_H

// moniotr.c
#define MONITOR_INTERVAL_IN_USEC 1000

// unsafe_functions.c
bool unsafe_is_hungry(t_philo philo);
bool unsafe_is_dead(t_philo philo, t_timeval *checked_at);

// log.c
void write_dead_log(t_philo *philo, t_timeval died_at);

#endif
