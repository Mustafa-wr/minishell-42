/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/23 14:50:15 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>
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
typedef struct t_redirect
{
	char		**file;
	char		**cmd;
}	t_redirect;

typedef struct t_pipe
{
	int			cmd_len;
	char		**cmds;
	char		***args; // {CMD1={CMD=ls, ARGS:ls, -l},CMD2={echo, h} }
	int			i;
	t_redirect	*line;
	t_env		*env;
}	t_pipe;

int		is_space(char *str);
/***************      pipes_parse         ****************/
int		check_pipes(t_pipe *pipe, char *line);

/***************    redirection_parse     ****************/
int		check_redirect(t_pipe *cmd);
char	*ft_add_spaces(char *str);

/***************      free_functions      ****************/
void	free_strings(char **av);
void	free_3d(char ***av);

/***************      quotes_parse        ****************/
void	clean_quotes(char *str);

// int	get_tokens(char **p_start, char *es, char **q, char **eq);
// int	peek(char **ps, char *es, char *toks); //this function to retun 1 if the ps is not '\n' and strchr

#endif