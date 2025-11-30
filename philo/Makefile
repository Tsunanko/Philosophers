NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c parse.c sim.c routine.c time_utils.c print.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -pthread -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
