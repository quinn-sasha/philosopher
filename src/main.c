#include "philo.h"
#include "parse_argument.h"

int main(int argc, char *argv[]) {
  t_data data;
  if (parse_argsument(&data.args, argc, argv) == PARSE_ERROR)
    return EXIT_FAILURE;
  init_data(&data);
  // start simulation
  // wait simulation ends
  return EXIT_SUCCESS;
}
