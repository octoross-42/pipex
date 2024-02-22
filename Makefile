NAME = pipex

SRCS = src/pipex.c \
		src/utils/split_argv.c \
		src/utils/split.c \
		src/utils/utils.c \
		src/gnl/gnl_here_doc.c \
		src/gnl/gnl_utils.c \
		src/printf/printf.c \
		src/printf/puts.c \
		src/printf/printf_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
bonus: $(NAME)

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
