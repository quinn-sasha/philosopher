/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:38:16 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:38:17 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	usleep_until(t_timeval end)
{
	t_timeval	now;
	suseconds_t	diff;

	while (true)
	{
		gettimeofday(&now, NULL);
		diff = timediff_usec(now, end);
		if (diff <= 0)
			return ;
		usleep(diff / 2);
	}
}

void	usleep_since(t_timeval start, int length_ms)
{
	t_timeval	end;

	end = timeadd_msec(start, length_ms);
	usleep_until(end);
}
