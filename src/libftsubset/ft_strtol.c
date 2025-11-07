#include "libftsubset.h"

static void preprocess_strtol(const char **str, bool *is_negative) {
  while (ft_isspace(**str))
    (*str)++;
  *is_negative = false;
  if (**str == '-')
    *is_negative = true;
  if (**str == '+' || **str == '-')
    (*str)++;
}

static bool is_overflow(unsigned long current, int next_digit, int base, int is_neg) {
  unsigned long max_quotient;
  unsigned long max_remainder;
  if (is_neg) {
    max_quotient = -(unsigned long)LONG_MIN / base;
    max_remainder = -(unsigned long)LONG_MIN % base;
  }
  else {
    max_quotient = (unsigned long)LONG_MAX / base;
    max_remainder = (unsigned long)LONG_MAX % base;
  }
  if (current > max_quotient)
    return true;
  if (current == max_quotient && next_digit > max_remainder)
    return true;
  return false;
}

static bool internal_strtol(const char **str, int base, unsigned long *result, bool *is_negative) {
  preprocess_strtol(str, is_negative);
  *result = 0;
  while (ft_isdigit(**str)) {
    int digit = **str - '0';
    if (is_overflow(*result, digit, base, *is_negative))
      return true;
    *result = *result * (unsigned long)base + digit;
    (*str)++;
  }
  return false;
}

// It only implements base 10
long ft_strtol(const char *nptr, char **endptr, int base) {
  if (base != 10)
    ft_putstr_fd("This ft_strtol() only takes base 10", STDERR_FILENO);
  unsigned long result;
  bool is_negative;
  bool is_overflow = internal_strtol(&nptr, base, &result, &is_negative);
  if (endptr != NULL)
    *endptr = (char *)nptr;
  if (!is_overflow) {
    if (is_negative)
      result = -result;
    return (long)result;
  }
  errno = ERANGE;
  if (is_negative)
    return LONG_MIN;
  return LONG_MAX;
}
