#include "libftsubset.h"

static void preprocess_strtol(const char **str, bool *is_negative) {
  while (ft_isspace(**str))
    *str++;
  *is_negative = false;
  if (**str == '-')
    is_negative = true;
  if (**str == '+' || **str == '-')
    *str++;
}

static bool is_overflow(unsigned long current, int next_digit, int base, int is_neg) {
  unsigned long cutoff
  if ()
}

static bool internal_strtol(const char **str, int base, unsigned long *result) {
  bool is_negative;
  preprocess_strtol(str, &is_negative);
  *result = 0;
  while (ft_isdigit(**str)) {
    int digit = **str - '0';

    *result = *result * (unsigned long)base + digit;
    *str++;
  }
  return false;
}

// It only implements base 10
long ft_strtol(const char *nptr, char **endptr, int base) {
  if (base != 10)
    ft_putstr_fd("This ft_strtol() only takes base 10", STDERR_FILENO);
  unsigned long result;
  bool is_error = internal_strtol(&nptr, base, &result);
  if (endptr != NULL)
    *endptr = (char *)nptr;
}
