/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsafe_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:37:16 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:37:17 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

bool	unsafe_is_hungry(t_philo philo)
{
	const int	max_eat = philo.data->args.max_eat;

	if (max_eat < 0)
		return (true);
	return (philo.eat_count < max_eat);
}

bool	unsafe_is_dead(t_philo philo, t_timeval *tp)
{
	t_timeval	now;
	const int	time_to_die_ms = philo.data->args.time_to_die_ms;
	t_timeval	deadline;
	suseconds_t	diff;

	gettimeofday(&now, NULL);
	rounddown_msec(&now);
	if (tp != NULL)
		*tp = now;
	deadline = timeadd_msec(philo.last_eat_at, time_to_die_ms);
	diff = timediff_usec(now, deadline);
	if (diff < 0)
		return (true);
	return (false);
}
