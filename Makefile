# Variables
NAME := philo
SRC_DIR := src
INCLUDE_DIR := include

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR)
RM := rm -f
RMDIR := rm -rf

SRCS := $(SRC_DIR)/main.c \
        $(SRC_DIR)/libftsubset/ft_atoi.c \
        $(SRC_DIR)/libftsubset/ft_isdigit.c \
        $(SRC_DIR)/libftsubset/ft_putchar_fd.c \
        $(SRC_DIR)/libftsubset/ft_putstr_fd.c \
        $(SRC_DIR)/libftsubset/ft_isspace.c \
        $(SRC_DIR)/libftsubset/ft_strtol.c \
        $(SRC_DIR)/simulation/log.c \
        $(SRC_DIR)/simulation/monitor.c \
        $(SRC_DIR)/simulation/philosopher.c \
        $(SRC_DIR)/simulation/simulation.c \
        $(SRC_DIR)/simulation/unsafe_functions.c \
				$(SRC_DIR)/utils/sleep.c \
				$(SRC_DIR)/utils/time.c \
				$(SRC_DIR)/parse_argument.c \
				$(SRC_DIR)/init.c


OBJ_DIR := objs
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# General rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RMDIR) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	./test.sh

data_race_test: CFLAGS += -g
data_race_test: re
	valgrind --tool=helgrind ./test.sh

memory_leak_test: CFLAGS += -g
memory_leak_test: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test.sh

.PHONY: all clean fclean re data_race_test test
