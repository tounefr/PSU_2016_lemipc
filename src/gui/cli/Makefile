##
## Makefile for  in /home/linder/PSU_2016_lemipc/src/gui/cli
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Sun Apr  2 19:04:22 2017 linder
## Last update Sun Apr  2 19:04:22 2017 linder
##

NAME = a.out

RM = rm -f

CC = gcc

SRCS =  gui.c

CFLAGS += -I ../../../include/ -L../../../ -llemipc_shared -pthread -lm -ldl -Wall -Wextra

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)

re: $(NAME)

clean:
	$(RM) gui.o

fclean: clean
	$(RM) $(NAME)
