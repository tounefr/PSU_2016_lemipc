##
## Makefile for  in /home/linder/cours/system unix/PSU_2016_lemipc
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Tue Mar 28 10:55:35 2017 linder
## Last update Sun Apr  2 16:09:11 2017 linder
##

CC =		gcc

RM =		rm -f

SRCS =		init.c		\
		rgb.c		\
		clear_win.c	\
		util.c		\

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-I ../../../include/ -L../../../ -llemipc_shared -pthread -lm -lSDL2

NAME =		a.out

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
