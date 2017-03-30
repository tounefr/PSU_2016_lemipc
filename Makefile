##
## Makefile for  in /home/linder/cours/system unix/PSU_2016_lemipc
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Tue Mar 28 10:55:35 2017 linder
## Last update Tue Mar 28 12:01:27 2017 linder
##

CC =		gcc

RM =		rm -f

SRCS =		main.c		\
		    util.c \
		    player.c \
		    movement.c \
		    signal.c \
		    init.c \
		    debug.c \
		    game.c

OBJS =		$(addprefix src/, $(SRCS:.c=.o))

#CFLAGS +=	-Wall -Wextra -Werror -L./ -I./include/
CFLAGS +=	-L./ -I./include/ -pthread -lm

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
