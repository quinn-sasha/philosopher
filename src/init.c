/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:51:55 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 19:5 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	init_forks(t_fork *forks, const int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		forks[i].id = i + 1;
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
}

/*
 * start_position: 各哲学者の開始時刻をIDに基づいて順位付けする
 * time_to_eat / k: 同じグループに属するk人の哲学者が time_to_eat 間で食事を始められるようにするためにずらす時間
 * start_offset_ms = 一人分のズレ幅 * 自分のスタートする順位
 */
static t_timeval	calc_initial_eat_at(int philo_id, t_data *data)
{
	const int	n = data->args.num_philo;
	const int	k = n / 2;
	const int	start_postion = (k * philo_id) % n;
	int			start_offset_ms;

	start_offset_ms = (data->args.time_to_eat_ms / k) * start_postion;
	if (n == 1)
		return (data->started_at);
	return (timeadd_msec(data->started_at, start_offset_ms));
}

static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].state = PH_SLEEPING;
		data->philosophers[i].eat_count = 0;
		data->philosophers[i].last_eat_at = data->started_at;
		data->philosophers[i].next_eat_at = calc_initial_eat_at(i + 1, data);
		data->philosophers[i].last_sleep_at = data->started_at;
		pthread_mutex_init(&data->philosophers[i].mutex, NULL);
		if (i == data->args.num_philo - 1)
		{
			data->philosophers[i].first = &data->forks[0];
			data->philosophers[i].second = &data->forks[i];
		}
		else
		{
			data->philosophers[i].first = &data->forks[i];
			data->philosophers[i].second = &data->forks[i + 1];
		}
		data->philosophers[i].data = data;
		i++;
	}
}

/*
n = 2k or n = 2k + 1
k = n / 2 (同時に食事をできる哲学者数)
optimal				interval = time_to_eat * (n / k)
n / k は別のタイミングで食事するグループ (だいたい 2 or 3)
optimal				interval = time_to_eat * (n
						/ k) (全てのグループが両方とも食事を終えるまでにかかる最低限の時間)
*/
static int	calculate_optimal_interval_ms(t_args *args)
{
	const int	n = args->num_philo;
	const int	k = args->num_philo / 2;
	const int	min_interval_ms = args->time_to_eat_ms + args->time_to_sleep_ms;
	int			result;

	if (n == 1)
		return (min_interval_ms);
	result = args->time_to_eat_ms * (n / k);
	if (result < min_interval_ms)
		return (min_interval_ms);
	return (result);
}

// started_at を現在の1秒後に設定して、全スレッドを同時に開始させる
void	init_data(t_data *data)
{
	gettimeofday(&data->started_at, NULL);
	data->started_at.tv_sec += 1;
	data->started_at.tv_usec = 0;
	data->optimal_interval_ms = calculate_optimal_interval_ms(&data->args);
	init_forks(data->forks, data->args.num_philo);
	init_philosophers(data);
	data->monitor.is_dead = false;
}
