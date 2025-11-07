#ifndef LIBFTSUBSET_H
#define LIBFTSUBSET_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#define TRUE 1
#define FALSE 0

int	ft_isdigit(int c);
int	ft_atoi(const char *str);
int	ft_putchar_fd(char c, int fd);
int	ft_putstr_fd(const char *str, int fd);
int	ft_isspace(int c);
long ft_strtol(const char *nptr, char **endptr, int base);

#endif
