
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
