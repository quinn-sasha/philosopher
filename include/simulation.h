#ifndef SIMULATION_H
#define SIMULATION_H

#define MONITOR_INTERVAL_IN_USEC 1000

bool unsafe_is_hungry(t_philo philo, int max_eat);
bool unsafe_is_dead(t_philo philo, t_timeval *checked_at);

#endif
