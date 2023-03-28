/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:40:39 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/27 04:42:30 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exec(t_cmds *p, t_pipe *c)
{
	t_vars	vars;

	vars.i = 0;
	// printf("r = %d\n", check_builtin(p, c, &vars));
	if (p[0].cmd)
	{
		if (check_builtin(p, c, &vars) == 1 && check_heredoc(p, c) == 0)
		{
			check_other(p, c);
		}
		else if (check_heredoc(p, c) == 1)
		{
			exec_heredoc(p, c);
		}
		free_all(c, p);
	}
}

int	check_builtin(t_cmds *p, t_pipe *c, t_vars *vars)
{
	int		x;

	x = 0;
	(void)vars;
	if (p[x].cmd)
	{
		if (ft_strncmp(p[x].cmd[0], "exit", 4) == 0)
		{
			// printf("eftxit\n");
			return (free_and_exit(c, p), 0);
		}
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
				return (ft_pwd(p, c), 0);
			else if (ft_strncmp(p[x].cmd[0], "env", 3) == 0)
				return (ft_env(p, c), 0);
		}
	}
	return (1);
}

void	check_other(t_cmds *p, t_pipe *c)
{
	// int		flag;

	c->i = 0;
	c->j = 0;
	// printf("\nentered exec\n");
	update_env(c);
	get_path(c->tmp_env, c);
	if (p->cmd_len == 1)
		normal_exec(p, c);
	else if (p->cmd_len > 1)
	{
		// printf("cmd_len = %d\n", p->cmd_len);
		multiple_pipes(p, c);
	}
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
	char	*cmd;

	i = 0;
	cmd = check_command_existence(p[0].cmd[0], c->m_path);
	printf("cmd = %s\n", cmd);
	i = fork();
	if (i == 0)
	{
		if (p[0].red_len > 0)
		{
			if (p[0].outs[0].flag == 0)
			{
				printf("fff\n");
				c->fd1 = check_input_redirect(p, c);
				if (c->fd1 > 2)
				{
					dup2(c->fd1, STDIN_FILENO);
					close(c->fd1);
				}
			}
			if (p[0].outs[p[0].red_len - 1].flag == 1)
			{
				// printf("r = %d\n", p[0].outs[p[0].red_len - 1].flag);
				c->fd2 = check_exec_rederict(p, c);
				if (c->fd2 > 2)
				{
					if (cmd)
					{
						dup2(c->fd2, STDOUT_FILENO);
						close(c->fd2);
					}
				}
			}
			if ((!cmd && !p[0].cmd) || (cmd == NULL && p[0].red_len > 0 && !p[0].cmd[0]))
			{
				free_and_exit(c, p);
			}
			else if (cmd == NULL && !p[0].cmd)
			{
				write(2, &p[0].cmd[0], ft_strlen(p[0].cmd[0]));
				write(2, "command not found :\n", 22);
				free_and_exit(c, p);
			}
		}
		if (!cmd && !p[0].cmd)
		{
			write(2, "command not found :\n", 22);
			free_and_exit(c, p);
		}
		else if (execve(cmd, p[0].cmd, c->tmp_env) < 0)
		{
			write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
			write(2, ": command not found\n", 21);
			free_and_exit(c, p);
		}
	}
	waitpid(i, NULL, 0);
	free(cmd);
}
