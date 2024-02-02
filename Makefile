NAME = pipex

SRCS = src/pipex.c \
		src/split/split.c \
		src/gnl/gnl.c \
		src/gnl/gnl_utils.c \
		src/printf/printf.c \
		src/printf/puts.c \
		src/printf/printf_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) -g3 -Iinclude -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)
	# ajouter cflags aussi au %.c 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
