/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/24 22:20:03 by abdamoha         ###   ########.fr       */
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
	int			env_count;
	char		**cmds;
	char		***args; // {CMD1={CMD=ls, ARGS:ls, -l},CMD2={echo, h} }
	int			i;
	char		**m_env;
	t_redirect	*line;
	t_env		*env;
}	t_pipe;

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

/***************      exec_part       ****************/

void	ms_exec(t_pipe *pipe);
void	ft_echo(t_pipe *p, int x, int y);
void	ft_pwd(t_pipe *p);
void	ft_env(t_pipe *p);
void	get_env(t_pipe *p, char **envp);
void	ft_cd(t_pipe *p);
void	ft_export(t_pipe *p);
void	ft_unset(t_pipe *p, int i, int j);
int		strncmp_orginal(const char *s1, const char *s2, unsigned int n);
#endif