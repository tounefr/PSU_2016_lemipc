
NAME = a.out

RM = rm -f

CC = gcc

SRCS =  gui.c

CFLAGS += -I ../../../include/ -L../../../ -llemipc_shared -pthread -lm -ldl

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)

re: $(NAME)

clean:
	$(RM) gui.o

fclean: clean
	$(RM) $(NAME)
