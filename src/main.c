/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:19:56 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 20:19:57 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_argument.h"
#include "philo.h"
#include "simulation.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parse_argsument(&data.args, argc, argv) == PARSE_ERROR)
		return (EXIT_FAILURE);
	init_data(&data);
	start_simulation(&data);
	wait_simulation_ends(data);
	return (EXIT_SUCCESS);
}
