/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:31:50 by squinn            #+#    #+#             */
/*   Updated: 2025/11/08 18:31:51 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsubset.h"

int	ft_putstr_fd(const char *str, int fd)
{
	int	num_bytes;

	if (str == NULL)
		return (ft_putstr_fd("(null)", fd));
	num_bytes = 0;
	while (*str)
	{
		num_bytes += ft_putchar_fd(*str, fd);
		str++;
	}
	return (num_bytes);
}
