/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:37:02 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:37:03 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"

// Monitor needs philosopher's mutex to access each eat_count and last_eat_at
// End conditions: Either someone dies or everyone eats max_eat times
static bool	should_continue_simulation(t_data *data)
{
	t_timeval	now;
	bool		is_dead_any;
	bool		is_eating;
	int			i;

	is_dead_any = false;
	is_eating = false;
	i = 0;
	while (!is_dead_any && i < data->args.num_philo)
	{
		pthread_mutex_lock(&data->philosophers[i].mutex);
		if (unsafe_is_hungry(data->philosophers[i]))
		{
			is_eating = true;
			if (unsafe_is_dead(data->philosophers[i], &now))
			{
				write_dead_log(&data->philosophers[i], now);
				is_dead_any = true;
			}
		}
		pthread_mutex_unlock(&data->philosophers[i].mutex);
		i++;
	}
	return (!is_dead_any && is_eating);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep_until(data->started_at);
	while (true)
	{
		usleep(MONITOR_INTERVAL_IN_USEC);
		if (!should_continue_simulation(data))
			return (NULL);
	}
}
