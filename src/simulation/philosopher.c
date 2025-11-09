/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:37:06 by squinn            #+#    #+#             */
/*   Updated: 2025/11/09 19:32:43 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"

/*
 * Return true(is_end) if num of philosophers are 1 or philosopher dies.
 * Philo calling unsafe_write_log() (which reads philo->last_eat_at) is safe
 * because no other thread tries to write it.
 */
static bool pickup_forks(t_philo *philo) {
	bool is_end = false;
	pthread_mutex_lock(&philo->first->mutex);
	is_end = unsafe_write_log(philo, "has taken a fork", NULL);
	if (is_end || philo->first->id == philo->second->id) {
		pthread_mutex_unlock(&philo->first->mutex);
		return true;
	}
	pthread_mutex_lock(&philo->second->mutex);
	is_end = unsafe_write_log(philo, "has taken a fork", NULL);
	if (is_end) {
		pthread_mutex_unlock(&philo->first->mutex);
		pthread_mutex_unlock(&philo->second->mutex);
	}
	return is_end;
}

static bool	philo_eat(t_philo *philo)
{
	const int	time_to_eat_ms = philo->data->args.time_to_eat_ms;
	bool		is_end;

	philo->state = PH_EATING;
	is_end = pickup_forks(philo);
	if (is_end)
		return (true);
	pthread_mutex_lock(&philo->mutex);
	philo->eat_count++;
	is_end = unsafe_write_log(philo, "is eating", &philo->last_eat_at);
	pthread_mutex_unlock(&philo->mutex);
	philo->next_eat_at = timeadd_msec(philo->last_eat_at,
			philo->data->optimal_interval_ms);
	if (!is_end)
		usleep_since(philo->last_eat_at, time_to_eat_ms);
	pthread_mutex_unlock(&philo->second->mutex);
	pthread_mutex_unlock(&philo->first->mutex);
	return (is_end);
}

static bool	philo_sleep(t_philo *philo)
{
	const int	time_to_sleep_ms = philo->data->args.time_to_sleep_ms;
	bool		is_end;

	philo->state = PH_SLEEPING;
	is_end = unsafe_write_log(philo, "is sleeping", &philo->last_sleep_at);
	if (!is_end)
		usleep_since(philo->last_sleep_at, time_to_sleep_ms);
	return (is_end);
}

static bool	philo_think(t_philo *philo)
{
	bool	is_end;

	philo->state = PH_THINKING;
	is_end = unsafe_write_log(philo, "is thinking", NULL);
	if (!is_end)
		usleep_until(philo->next_eat_at);
	return (is_end);
}

/*
Philosopher calling unsafe_is_hungry is safe because
no other thread tries to write it.
*/
void	*philosopher_thread(void *arg)
{
	t_philo	*philo;
	bool	is_end;

	philo = (t_philo *)arg;
	usleep_until(philo->data->started_at);
	is_end = false;
	while (!is_end && unsafe_is_hungry(*philo))
	{
		if (philo->state == PH_THINKING)
			is_end = philo_eat(philo);
		else if (philo->state == PH_EATING)
			is_end = philo_sleep(philo);
		else if (philo->state == PH_SLEEPING)
			is_end = philo_think(philo);
		else
			return (NULL);
	}
	return (NULL);
}
