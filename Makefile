NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I ./include
SRCS_PATH	=./src

RM		=rm -rf

SRCS	=$(SRCS_PATH)/main.c\
		$(SRCS_PATH)/utils.c\
		$(SRCS_PATH)/philo.c\
		$(SRCS_PATH)/set_table.c\
		$(SRCS_PATH)/simulation.c\

OBJS	= $(SRCS:.c=.o)

INCLUDE	= -pthread
FLAGS = -g -fsanitize=thread

HEADER	= ./include/philo.h

# ----- COLORS ----- #
GREEN  = \033[32;1m
RED    = \033[31;49;1m
YELLOW = \033[33;49;1m
RESET  = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(CFLAGS) $(FLAGS) -o $(NAME) $(OBJS)
	@ echo "\033[31mPhilo created\033[0m"

clean:
	@ rm -f $(OBJS)
	@ echo "\033[33mObject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@ echo "\033[33mProject removed\033[0m"

re: fclean all

.PHONY:	all clean fclean re



