/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/27 21:08:42 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_code = 0;

void	clean_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	j = 0;
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	ms_main_helper(t_pipe *pipe, t_cmds *cmds, char *read)
{
	if (is_space(read))
		return (1);
	if (!check_redirect(read))
	{
		printf("syntax error near unexpected token \n");
		add_history(read);
		g_exit_code = 258;
		return (1);
	}
	else if (!check_pipes(pipe, read, cmds))
	{
		printf("Error\n");
		add_history(read);
		g_exit_code = 258;
		return (1);
	}
	return (0);
}

void	main_helper(t_pipe *pipe, t_cmds *cmds)
{
	pipe->fdin = dup(0);
	pipe->fdout = dup(1);
	ms_exec(cmds, pipe);
	dup2(pipe->fdin, STDIN_FILENO);
	dup2(pipe->fdout, STDOUT_FILENO);
	close(pipe->fdin);
	close(pipe->fdout);
}

void	main_init(t_pipe *pipe)
{
	pipe->m_path = NULL;
	pipe->fdin = 0;
	pipe->fdout = 0;
	pipe->ch = 0;
	pipe->cr = 0;
	pipe->p_f1 = 0;
	pipe->p_f2 = 0;
	pipe->e_fd = 0;
}
