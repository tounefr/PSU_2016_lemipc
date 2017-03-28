##
## Makefile for  in /home/linder/cours/system unix/PSU_2016_lemipc
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Tue Mar 28 10:55:35 2017 linder
## Last update Tue Mar 28 10:59:41 2017 linder
##

CC =		gcc

RM =		rm -f

SRCS =		main.c

OBJS =		$(addprefix src/, $(SRCS:.c=.o))

CFLAGS +=	-Wall -Wextra -Werror -L./ -I./include/

NAME =		lemipc

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
