/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 19:40:32 by mradwan          ###   ########.fr       */
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

static void	main_helper(t_pipe *pipe, t_cmds *cmds)
{
	pipe->fdin = dup(0);
	pipe->fdout = dup(1);
	ms_exec(cmds, pipe);
	dup2(pipe->fdin, STDIN_FILENO);
	dup2(pipe->fdout, STDOUT_FILENO);
	close(pipe->fdin);
	close(pipe->fdout);
}

static void	main_init(t_pipe *pipe)
{
	pipe->m_path = NULL;
	pipe->fdin = 0;
	pipe->fdout = 0;
	pipe->ch = 0;
	pipe->cr = 0;
	pipe->p_f1 = 0;
	pipe->p_f2 = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipe;
	t_cmds	*cmds;
	char	*read;

	(void)av;
	(void)ac;
	cmds = NULL;
	get_env(&pipe, envp);
	fill_export(&pipe);
	g_exit_code = 0;
	main_init(&pipe);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		read = readline("\x1B[31mbash-3.3$\e[0m ");
		if (!read)
			return (free_and_exit_2(&pipe, cmds), printf("exit\n"), 0);
		if (ms_main_helper(&pipe, cmds, read))
			continue ;
		files_saving(&pipe, &cmds);
		main_helper(&pipe, cmds);
		add_history(read);
	}
}
