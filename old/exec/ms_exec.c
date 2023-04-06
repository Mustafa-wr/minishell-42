/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:40:39 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 18:21:41 by mradwan          ###   ########.fr       */
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

void	normal_e(t_cmds *p, t_pipe *c)
{
	if (p[0].red_len > 0)
		output_red(p, c, c->cmd_exec);
	if (!c->cmd_exec)
	{
		write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
		if (p[0].cmd[0])
			write(2, ": command not found\n", 21);
		g_exit_code = 127;
		free(c->cmd_exec);
		free_and_exit(c, p);
	}
	else if (execve(c->cmd_exec, p[0].cmd, c->tmp_env) < 0)
	{
		perror("execve : is directory");
		g_exit_code = 126;
		free(c->cmd_exec);
		free_and_exit(c, p);
	}
}

void	normal_e2(t_cmds *p, struct stat **fs)
{
	if (!ft_strchr(p[0].cmd[0], '.') && ft_strchr(p[0].cmd[0], '/'))
	{
		if (stat(p[0].cmd[0], *fs) != 0)
		{
			perror("stat");
			g_exit_code = 127;
			return ;
		}
	}
	else if (ft_strchr(p[0].cmd[0], '.') && ft_strchr(p[0].cmd[0], '/'))
	{
		if (stat(p[0].cmd[0], *fs) != 0)
		{
			perror("stat");
			g_exit_code = 127;
			return ;
		}
	}
}

void	normal_exec(t_cmds *p, t_pipe *c)
{
	int			i;
	struct stat	fs;
	int			status;

	c->ch = 1;
	if (!ft_strchr(p[0].cmd[0], '.') && ft_strchr(p[0].cmd[0], '/'))
	{
		if (stat(p[0].cmd[0], &fs) != 0)
		{
			perror("stat");
			g_exit_code = 127;
			return ;
		}
	}
	else if (ft_strchr(p[0].cmd[0], '.') && ft_strchr(p[0].cmd[0], '/'))
	{
		if (stat(p[0].cmd[0], &fs) != 0)
		{
			perror("stat");
			g_exit_code = 127;
			return ;
		}
	}
	// normal_e2(p, &fs);
	c->cmd_exec = check_command_existence(p[0].cmd[0], c->m_path);
	i = fork();
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	if (i == 0)
		normal_e(p, c);
	status = 0;
	waitpid(i, &status, 0);
	if (WIFEXITED(status))
	g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = get_sig_status(WTERMSIG(status));
	free(c->cmd_exec);
	c->cmd_exec = NULL;
	c->ch = 0;
}
