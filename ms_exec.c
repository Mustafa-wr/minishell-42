/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:40:39 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/05 17:48:15 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(t_cmds *p, t_pipe *c)
{
	t_vars	vars;

	vars.i = 0;
	check_builtin(p, c, &vars);
	// printf("v = %d", vars.i);
	// if (vars.i == 0)
	check_other(p, c);
}

void	check_builtin(t_cmds *p, t_pipe *c, t_vars *vars)
{
	int		x;

	x = 0;
	(void)vars;
	if (ft_strncmp(p[x].cmd[0], "exit", 4) == 0)
		free_and_exit(c, p);
	else if (ft_strncmp(p[x].cmd[0], "cd", 2) == 0)
		ft_cd(p, x, 0, c);
	else if (ft_strncmp(p[x].cmd[0], "export", 6) == 0)
		ft_export(c, p, x, 0);
	else if (ft_strncmp(p[x].cmd[0], "unset", 5) == 0)
		ft_unset(p, x, 0, c);
	else
	{
		ft_tolower(p[x].cmd[0]);
		if (ft_strncmp(p[x].cmd[0], "echo", 4) == 0)
			ft_echo(p, x, 0, c);
		else if (ft_strncmp(p[x].cmd[0], "pwd", 3) == 0)
			ft_pwd(p, c);
		else if (ft_strncmp(p[x].cmd[0], "env", 3) == 0)
			ft_env(p, c);
	}
}

void	check_other(t_cmds *p, t_pipe *c)
{
	// int		flag;

	c->i = 0;
	c->j = 0;
	// printf("cmd_len = %d\n", p->cmd_len);
	c->m_path = check_env_for_path(c->m_env);
	if (p->cmd_len == 1)
		normal_exec(p, c);
	else if (p->cmd_len > 1)
		multiple_pipes(p, c);
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
	// printf("cmd = %s", cmd);
	// exit(0);
	i = fork();
	if (i == 0)
	{
		if (execve(cmd, p[0].cmd, c->tmp_env) < 0)
		{
			printf("command not found :%s\n", p[0].cmd[0]);
			return ;
		}
	}
	waitpid(i, NULL, 0);
}
