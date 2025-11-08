/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:30:09 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:30:10 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ARGUMENT_H
# define PARSE_ARGUMENT_H

# include "philo.h"

# define PARSE_ERROR -1
# define PARSE_SUCCESS 0
# define INT_MAX_STRING "2147483647"
# define MIN_NUM_ARGUMENTS 5

int	parse_argsument(t_args *args, int argc, char *argv[]);

#endif
