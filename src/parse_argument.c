#include "philo.h"
#include "parse_argument.h"
#include "libftsubset.h"

static bool is_numeric(const char *str) {
  if (*str == '\0')
    return false;
  int i = 0;
  while (str[i]) {
    if (!ft_isdigit(str[i]))
      return false;
    i++;
  }
  return true;
}

static int get_non_negative_int(const char *str) {
  if (!is_numeric(str))
    return -1;
  long result = ft_strtol(str, NULL, 10);
  if (errno == ERANGE)
    return -1;
  if (result > INT_MAX || result < INT_MIN)
    return -1;
  return (int)result;
}

// Reference: https://github.com/usatie/philosophers/blob/master/philo/src/argsparse/argsparse.c
static int usage_error(void) {
	ft_putstr_fd(
		"USAGE:\n"
		"  ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
		"\n"
		"DESCRIPTION:\n"
		"  - number_of_philosophers is valid between 1 to MAX_PHILO.\n"
		"    (Default value for MAX_PHILO is 200.)\n"
		"  - number_of_times_each_philosopher_must_eat must be non-zero\n"
		"    value. When it is not specified, the simulation\n"
		"    does not end until someone dies.\n"
		"VALID EXAMPLE:\n"
		"  ./philo 5 200 100 100\n"
		"  ./philo 5 200 100 100 10\n"
		"INVALID EXAMPLE:\n"
		"  ./philo 5 500 100\n"
    "  ./philo 5 500 100 100 -10"
		"  ./philo 5 500 100 100 10 100\n"
		"  ./philo 5 9999999999999999 100 100 10\n",
		STDERR_FILENO);
  return PARSE_ERROR;
}

int parse_argsument(t_args *args, int argc, char *argv[]) {
  if (argc != MIN_NUM_ARGUMENTS && argc != MIN_NUM_ARGUMENTS + 1)
    return usage_error();
  args->num_philo = get_non_negative_int(argv[1]);
  if (args->num_philo <= 0 || args->num_philo > MAX_PHILO)
    return usage_error();
  args->time_to_die_ms = get_non_negative_int(argv[2]);
  if (args->time_to_die_ms < 0)
    return usage_error();
  args->time_to_eat_ms = get_non_negative_int(argv[3]);
  if (args->time_to_die_ms < 0)
    return usage_error();
  args->time_to_sleep_ms = get_non_negative_int(argv[4]);
  if (args->time_to_die_ms < 0)
    return usage_error();
  if (argc == MIN_NUM_ARGUMENTS) {
    args->max_eat = -1;
    return PARSE_SUCCESS;
  }
  args->max_eat = get_non_negative_int(argv[5]);
  if (args->max_eat <= 0)
    return usage_error();
  return PARSE_SUCCESS;
}
