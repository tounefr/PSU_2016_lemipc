##
## Makefile for  in /home/linder/cours/system unix/PSU_2016_lemipc
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Tue Mar 28 10:55:35 2017 linder
## Last update Sat Apr  1 17:33:32 2017 linder
##

CC =		gcc

RM =		rm -f

SRCS =		init.c		\
		rgb.c		\
		clear_win.c	\
		util.c		\

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-lSDL2 -lm -I../../../include


NAME =		graph

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
