#include "philo.h"
#include "parse_argument.h"
#include "simulation.h"

int main(int argc, char *argv[]) {
  t_data data;
  if (parse_argsument(&data.args, argc, argv) == PARSE_ERROR)
    return EXIT_FAILURE;
  init_data(&data);
  start_simulation(&data);
  wait_simulation_ends(data);
  return EXIT_SUCCESS;
}
