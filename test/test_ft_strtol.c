#include "libftsubset.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    dprintf(STDERR_FILENO, "Usage: ./a.out string_to_convert base\n");
    return 1;
  }
  long result = ft_strtol(argv[1], NULL, ft_atoi(argv[2]));
  if (errno == ERANGE) {
    printf("Overflow: returned [%ld]\n", result);
    return 1;
  }
  printf("Result: [%ld]\n", result);
  return 0;
}
