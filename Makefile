NAME = minishell

SRCS =	parsing/ms_parse.c					\
		parsing/ms_parse_redirect.c			\
		parsing/ms_pipe_parse.c				\
		parsing/ms_parse_utils.c			\
		parsing/ms_add_spaces.c				\
		parsing/ms_get_cmd.c				\
		parsing/ms_dollar_han.c				\
		parsing/get_nv.c					\
		ms_free_functions.c					\
		exec/ms_exec.c                      \
		exec/ms_builtins.c                  \
		exec/ms_utils2.c                    \
		exec/ms_extra_utils.c               \
		exec/ms_utils3.c                    \
		exec/ms_export.c                    \
		exec/ms_exec_utils.c                \
		exec/ms_exit.c                      \
		exec/ms_multiple_pipe.c             \
		exec/ms_multiple_pipes_utils.c      \
		exec/ms_builtins_utils.c            \
		exec/ms_redierction.c               \
		exec/ms_heredoc.c      

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -g3 -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.1/include #-fsanitize=address

all : $(NAME)

$(NAME): $(OBJS)
	make -C ./libft && make bonus -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ./libft -lft -lreadline -L /usr/local/Cellar/readline/8.1/lib/

clean:
	cd libft && make fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks:
	valgrind --suppressions=$(PWD)/valgrind_readline_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
