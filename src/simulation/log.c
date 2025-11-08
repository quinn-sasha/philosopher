/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:36:52 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:36:53 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"

// It needs mutex for printed_dead_log and monitor.is_dead to write them
// Death logs are shown only once
static void	unsafe_write_dead_log(t_philo *philo, t_timeval died_at)
{
	static bool	printed_dead_log = false;
	int			timestamp_ms;

	if (printed_dead_log)
		return ;
	philo->data->monitor.is_dead = true;
	timestamp_ms = timediff_msec(philo->data->started_at, died_at);
	printf("%d %d died\n", timestamp_ms, philo->id);
	printed_dead_log = true;
}

void	write_dead_log(t_philo *philo, t_timeval died_at)
{
	pthread_mutex_lock(&philo->data->monitor.mutex);
	unsafe_write_dead_log(philo, died_at);
	pthread_mutex_unlock(&philo->data->monitor.mutex);
}

/*
 * It is unsafe if monitor tries to read last_eat_at without philo's mutex.
 * Return true if someone dies, otherwise false.
 */
bool	unsafe_write_log(t_philo *philo, const char *message, t_timeval *tp)
{
	bool		is_end;
	t_timeval	now;
	int			timestamp_ms;

	pthread_mutex_lock(&philo->data->monitor.mutex);
	if (philo->data->monitor.is_dead)
		is_end = true;
	else
	{
		is_end = unsafe_is_dead(*philo, &now);
		if (is_end)
			unsafe_write_dead_log(philo, now);
		else
		{
			timestamp_ms = timediff_msec(philo->data->started_at, now);
			printf("%d %d %s\n", timestamp_ms, philo->id, message);
		}
		if (tp != NULL)
			*tp = now;
	}
	pthread_mutex_unlock(&philo->data->monitor.mutex);
	return (is_end);
}
