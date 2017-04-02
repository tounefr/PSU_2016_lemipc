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
		    player.c \
		    player2.c \
		    movement.c \
		    signal.c \
		    init.c \
		    debug.c \
		    game.c \
		    util.c \
		    pos.c \
		    pos2.c \
		    share_mem.c \
		    ennemy.c

CFLAGS +=	-I ../../include/ -L../../ -llemipc_shared -pthread -lm -ldl -Wall -Wextra

OBJS =		$(SRCS:.c=.o)

#CFLAGS +=	-Wall -Wextra -Werror -I../../include/

NAME =		lemipc

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) $(CFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
