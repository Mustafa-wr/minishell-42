/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/28 16:36:02 by mradwan          ###   ########.fr       */
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

// evecve(char)
// typedef struct t_redirect
// {
// 	char		*file;
// }	t_redirect;

typedef struct s_vars
{
	int i;
    int j;
    int space_found;
    int quote_char;
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
	int red_len;// = 4
	char **cmd;// [0]-ls.. [1] -la
	t_redirect  *outs;
}	t_cmds;

	/**
	 * [0]->flag = 1
	 * [0]->red_name = pwd
	 * 	 * [0]->flag = 1
	 * [0]->red_name = lsss
	 * 	 * [0]->flag = 1
	 * [0]->red_name = out
	 * 	 * [0]->flag = 2
	 * [0]->red_name = outfile
	 */


typedef struct t_pipe
{
	int			cmd_len;
	char		**cmds;//
	char		**tmp;
	char		***args; // {CMD1={CMD=ls, ARGS:ls, -l},CMD2={echo, h} }
	int			i;
	int			num_of_pipes;
	int			*ibq;
	t_env		*env;
}	t_pipe;

int		is_space(char *str);
/***************      pipes_parse         ****************/
int	check_pipes(t_pipe *pipe, char *line, t_cmds *cmds);

/***************    redirection_parse     ****************/
int		check_redirect(t_pipe *cmd);
char	*ft_add_spaces(char *str);
void 	replace_spaces_tabs(char *str);

/***************      free_functions      ****************/
void	free_strings(char **av);
void	free_3d(char ***av);

/***************      quotes_parse        ****************/
void	clean_quotes(char *str);
void	files_saving(t_pipe *pipe, t_cmds	*cmds);

// int	get_tokens(char **p_start, char *es, char **q, char **eq);
// int	peek(char **ps, char *es, char *toks); //this function to retun 1 if the ps is not '\n' and strchr

#endif