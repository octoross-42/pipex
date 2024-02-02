NAME = pipex

SRCS = src/pipex.c \
		src/utils/utils.c \
		src/utils/gnl.c \
		src/utils/gnl_utils.c

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

flcean: clean
	rm -f $(NAME)

re: flcean all
