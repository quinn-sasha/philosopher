/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsubset.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:29:53 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:29:54 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSUBSET_H
# define LIBFTSUBSET_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(const char *str, int fd);
int		ft_isspace(int c);
long	ft_strtol(const char *nptr, char **endptr, int base);

#endif
