/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:40:39 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/02 04:29:32 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exec(t_cmds *p, t_pipe *c)
{
	if (p[0].cmd)
	{
		if (check_builtin(p, c) == 1)
		{
			check_other(p, c);
		}
		free_all(c, p);
	}
}

int	check_builtin(t_cmds *p, t_pipe *c)
{
	int		x;

	x = 0;
	if (p[x].cmd && p->cmd_len == 1)
	{
		if (ft_strncmp(p[x].cmd[0], "exit", 4) == 0)
			return (ft_exit(c, p), 0);
		else if (ft_strncmp(p[x].cmd[0], "cd", 2) == 0)
			return (ft_cd(p, x, 0, c), 0);
		else if (ft_strncmp(p[x].cmd[0], "export", 6) == 0)
			return (ft_export(c, p, x, 0), 0);
		else if (ft_strncmp(p[x].cmd[0], "unset", 5) == 0)
			return (ft_unset(p, x, 0, c), 0);
		else
		{
			ft_tolower(p[x].cmd[0]);
			if (ft_strncmp(p[x].cmd[0], "echo", 4) == 0)
				return (ft_echo(p, x, 0, c), 0);
			else if (ft_strncmp(p[x].cmd[0], "pwd", 3) == 0)
				return (ft_pwd(p, c, 0), 0);
			else if (ft_strncmp(p[x].cmd[0], "env", 3) == 0)
				return (ft_env(p, c, 0), 0);
		}
	}
	return (1);
}

void	check_other(t_cmds *p, t_pipe *c)
{
	c->i = 0;
	c->j = 0;
	update_env(c);
	get_path(c->tmp_env, c);
	if (p->cmd_len == 1)
		normal_exec(p, c);
	else if (p->cmd_len > 1)
		multiple_pipes(p, c);
	if (c->m_path)
	{
		free_strings(c->m_path);
		c->m_path = NULL;
	}
}

int	check_for_redirction(t_cmds *p, t_pipe *c)
{
	int		counter;

	counter = 0;
	c->i = 0;
	c->j = 0;
	while (c->i < p->cmd_len)
	{
		c->j = 0;
		while (p[c->i].cmd[c->j])
		{
			counter = 0;
			while (p[c->i].cmd[c->j][counter])
			{
				if (p[c->i].cmd[c->j][counter] == '>'
				|| p[c->i].cmd[c->j][counter] == '<')
					return (1);
				counter++;
			}
			c->j++;
		}
		c->i++;
	}
	return (0);
}

void	normal_exec(t_cmds *p, t_pipe *c)
{
	int		i;

	c->cmd_exec = check_command_existence(p[0].cmd[0], c->m_path);
	i = fork();
	if (i == 0)
	{
		if (p[0].red_len > 0)
		{
			input_red(p, c);
			output_red(p, c, c->cmd_exec);
		}
		if (!c->cmd_exec)
		{
			write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
			if (p[0].cmd[0])
				write(2, ": command not found\n", 21);
			g_exit_code = 127;
			free_and_exit(c, p);
		}
		else if (execve(c->cmd_exec, p[0].cmd, c->tmp_env) < 0)
		{
			perror("execve : is directory");
			free_and_exit(c, p);
			g_exit_code = 126;
		}
	}
	int	status;
	waitpid(i, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_code = WEXITSTATUS(status);
		// if (g_exit_code == 1)
		// 	g_exit_code = 127;
		// else
		// 	g_exit_code = 0;
	}
	else if (WIFSIGNALED(status))
	{
		g_exit_code = WTERMSIG(status) + 128;
	}
	free(c->cmd_exec);
}
