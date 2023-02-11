/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/10 19:09:06 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <readline/history.h>

typedef struct t_pipe
{
	int		cmd_len;
	char	**cmds;
} t_pipe;

typedef struct s_env
{
	char **path;
	char *user;
	char *home;
} t_env;


int	get_tokens(char **p_start, char *es, char **q, char **eq);
int	peek(char **ps, char *es, char *toks); //this function to retun 1 if the ps is not '\n' and strchr

#endif