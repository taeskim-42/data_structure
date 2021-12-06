SRCS = srcs/assignment05/arrayqueue.c

INCS = includes/

NAME = ArrayQueue

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INCS)


OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean : rm -f $(OBJS)

fclean : clean
		rm -f $(OBJS)

re : fclean all

.PHONY: all clean fclean re