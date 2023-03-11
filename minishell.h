/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/11 20:01:23 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>

int	g_exit_code;

typedef struct s_env
{
	char	**path;
	char	*user;
	char	*home;
}	t_env;

typedef struct s_vars
{
	int	i;
	int	j;
	int	h;
	int	empty;
	int	space_found;
	int	quote_char;
	int	x;
	int	start;
	int	len;
	int	xy;
	int	in_d_quotes;
	int	in_quotes;
}	t_vars;

enum e_types
{
	IN_FILE,
	OUT_FILE,
	APPEND,
	HERE_DOC,
};

typedef struct s_redirect
{
	int		flag;
	char	*file_name;
}	t_redirect;

//< pwd ls < lsss < out > outfile -la | pwd cat | grep -n hello | cat -e
//< ls pwd
typedef struct s_cmds
{
	int			red_len;
	int			cmd_len;
	char		**cmd; // "ls" -la -l NULL
	t_redirect	*outs;
}	t_cmds;

typedef struct t_pipe
{
	int		cmd_len;
	char	**cmds;
	char	**env;
	int		env_count;
	int		i;
}	t_pipe;

void	enviro(t_pipe *s, char **envp);
char *my_getenv(const char *name, t_pipe *pipe);

/***************      parse_tool          ****************/
int		is_space(char *str);
char	*ft_add_spaces(char *str);
void	replace_spaces_tabs(char *str);

/***************      pipes_parse         ****************/
int		check_pipes(t_pipe *pipe, char *line, t_cmds *cmds);
void	dollar_expansion(char **str, t_pipe *pipe);

/***************    redirection_parse     ****************/
int		check_redirect(char *str);
int		num_of_redirects(char *str);
void	remove_substr(char *s, unsigned int start, size_t len);

/***************      free_functions      ****************/
void	free_strings(char **av);
void	free_all(t_pipe *pipe, t_cmds *cmd);

/***************      quotes_parse        ****************/
void	clean_quotes(char *str);
void	files_saving(t_pipe *pipe, t_cmds **tmp);

void	get_env(t_pipe *p, char **envp);

#endif