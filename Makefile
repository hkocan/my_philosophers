NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I ./include
SRCS_PATH	=./src

RM		=rm -rf

SRCS	=	$(SRCS_PATH)/main.c\
			$(SRCS_PATH)/free.c\
			$(SRCS_PATH)/utils.c\
			$(SRCS_PATH)/action.c\
			$(SRCS_PATH)/simulation.c\
			$(SRCS_PATH)/setup_simulation.c\

OBJS	= $(SRCS:.c=.o)

INCLUDE	= -pthread
FLAGS = -g -fsanitize=thread

HEADER	= ./include/philo.h

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



