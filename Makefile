NAME = pipex

SRCS = src/pipex.c \
		src/pipex/infile_outfile.c \
		src/pipex/parsing.c \
		src/pipex/pipes.c \
		src/utils/split_argv.c \
		src/utils/split.c \
		src/utils/utils.c \
		src/gnl/gnl_here_doc.c \
		src/gnl/gnl_utils.c \
		src/printf/printf.c \
		src/printf/puts.c \

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g3 -Iinclude -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
