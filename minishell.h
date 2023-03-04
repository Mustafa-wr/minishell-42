/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/04 19:40:53 by mradwan          ###   ########.fr       */
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
	int	space_found;
	int	quote_char;
	int	x;
	int	start;
	int	xy;
	int	in_d_quotes;
	int	in_quotes;
}	t_vars;

enum e_types
{
	IN_FILE,
	OUT_FILE,
	APPEND_OUT,
	APPEND_IN,
};

typedef struct s_redirect
{
	int		flag;
	char	*file_name;
}	t_redirect;

//< pwd ls < lsss < out > outfile -la | pwd cat | grep -n hello | cat -e

typedef struct s_cmds
{
	int			red_len;
	int			cmd_len;
	char		**cmd;
	t_redirect	*outs;
}	t_cmds;

typedef struct t_pipe
{
	int			cmd_len;
	char		**cmds;
	int			i;
}	t_pipe;

/***************      parse_tool          ****************/
int		is_space(char *str);
char	*ft_add_spaces(char *str);
void	replace_spaces_tabs(char *str);

/***************      pipes_parse         ****************/
int		check_pipes(t_pipe *pipe, char *line, t_cmds *cmds);

/***************    redirection_parse     ****************/
int		check_redirect(t_pipe *cmd);
int		num_of_redirects(char *str);
void	remove_substr(char *s, unsigned int start, size_t len);

/***************      free_functions      ****************/
void	free_strings(char **av);
void	free_3d(char ***av);
void	free_all(t_pipe *pipe, t_cmds *cmd);

/***************      quotes_parse        ****************/
void	clean_quotes(char *str);
void	files_saving(t_pipe *pipe, t_cmds **tmp);

#endif