##
## Makefile for  in /home/linder/PSU_2016_lemipc/src/common
## 
## Made by linder
## Login   <linder@epitech.net>
## 
## Started on  Sun Apr  2 18:45:13 2017 linder
## Last update Sun Apr  2 18:45:15 2017 linder
##

NAME = a.out

CC = gcc

RM = rm -f

all: re

$(NAME):
	$(CC) -c -I ../../include -fPIC shared_lemipc.c
	$(CC) $(CFLAGS) -shared -o $(NAME) shared_lemipc.o

re: $(NAME)

clean:
	$(RM) shared_lemipc.o

fclean: clean
	$(RM) $(NAME)

.PHONY: re clean fclean all
