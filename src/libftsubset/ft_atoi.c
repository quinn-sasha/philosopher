#include "libftsubset.h"

int	ft_atoi(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return ((int)(sign * result));
		result = (str[i] - '0') + result * 10;
		i++;
	}
	return ((int)(sign * result));
}
