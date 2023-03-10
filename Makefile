NAME = minishell

SRCS =	parsing/ms_parse.c				\
		parsing/ms_parse_redirect.c		\
		parsing/ms_pipe_parse.c			\
		parsing/ms_parse_utils.c		\
		parsing/ms_add_spaces.c			\
		parsing/ms_get_cmd.c			\
		ms_free_functions.c				\
		parsing/ms_dollar_han.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -g3 -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.1/include #-fsanitize=address

all : $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ./libft -lft -lreadline -L /usr/local/Cellar/readline/8.1/lib/

clean:
	cd libft && make fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all