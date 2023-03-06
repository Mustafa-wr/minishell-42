NAME = minishell

SRCS =	libft/ft_memset.c				\
		libft/ft_bzero.c				\
		libft/ft_memcpy.c				\
		libft/ft_memmove.c 				\
		libft/ft_memchr.c				\
		libft/ft_memcmp.c				\
		libft/ft_strlen.c				\
		libft/ft_isalpha.c				\
		libft/ft_isdigit.c				\
		libft/ft_isalnum.c				\
		libft/ft_isascii.c				\
		libft/ft_isprint.c				\
		libft/ft_toupper.c				\
		libft/ft_tolower.c				\
		libft/ft_strchr.c				\
		libft/ft_strrchr.c				\
		libft/ft_strncmp.c				\
		libft/ft_strlcpy.c				\
		libft/ft_strlcat.c				\
		libft/ft_strnstr.c				\
		libft/ft_atoi.c					\
		libft/ft_calloc.c				\
		libft/ft_strdup.c				\
		libft/ft_putchar_fd.c			\
		libft/ft_putstr_fd.c			\
		libft/ft_substr.c				\
		libft/ft_strjoin.c				\
		libft/ft_strtrim.c				\
		libft/ft_split.c				\
		libft/ft_striteri.c				\
		libft/ft_itoa.c					\
		libft/ft_putendl_fd.c			\
		libft/ft_strmapi.c				\
		parsing/ms_parse.c				\
		parsing/ms_parse_redirect.c		\
		parsing/ms_pipe_parse.c			\
		parsing/ms_parse_utils.c		\
		parsing/ms_add_spaces.c			\
		parsing/ms_get_cmd.c			\
		ms_free_functions.c				\
		parsing/ms_dollar_han.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.1/include -fsanitize=address

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L /usr/local/Cellar/readline/8.1/lib/

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all