/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:45:28 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/11 00:26:47 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins_pipes(t_cmds *p, t_pipe *c, int fd, int j)
{
	if (p[j].cmd)
	{
		if (ft_strncmp(p[j].cmd[0], "exit", 4) == 0)
			return (ft_exit(c, p), 0);
		else if (ft_strncmp(p[j].cmd[0], "cd", 2) == 0)
			return (ft_cd_p(p, j, fd, c), 0);
		else if (ft_strncmp(p[j].cmd[0], "export", 6) == 0)
			return (ft_export_p(c, p, j, fd), 0);
		else if (ft_strncmp(p[j].cmd[0], "unset", 5) == 0)
			return (ft_unset_p(p, j, fd, c), 0);
		else
		{
			ft_tolower(p[j].cmd[0]);
			if (ft_strncmp(p[j].cmd[0], "echo", 4) == 0)
				return (ft_echo_p(p, j, fd, c), 0);
			else if (ft_strncmp(p[j].cmd[0], "pwd", 3) == 0)
				return (ft_pwd_p(p, c, fd), 0);
			else if (ft_strncmp(p[j].cmd[0], "env", 3) == 0)
				return (ft_env_p(p, c, fd), 0);
		}
	}
	return (1);
}

int	input_check(t_cmds *p, t_pipe *c, int j)
{
	c->i = 0;
	while (c->i < p[j].red_len)
	{
		if (p[j].outs[c->i].flag == 0 || p[j].outs[c->i].flag == 3)
			return (1);
		c->i++;
	}
	return (0);
}

int	output_check(t_cmds *p, t_pipe *c, int j)
{
	c->i = 0;
	while (c->i < p[j].red_len)
	{
		if (p[j].outs[c->i].flag == 1 || p[j].outs[c->i].flag == 2)
			return (1);
		c->i++;
	}
	return (0);
}

void	exit_once(t_cmds *p, t_pipe *c)
{
	(void)p;
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);
	if (c->cmd_exec)
		free(c->cmd_exec);
	free_all(c, p);
	close(c->fdin);
	close(c->fdout);
	exit(g_exit_code);
}

void	check_and_exit(t_pipe *c)
{
	if (c->p_f1 == 1)
	{
		close(c->fd[0][0]);
		close(c->fd[0][1]);
	}
	if (c->p_f2 == 1)
	{
		close(c->fd[1][0]);
		close(c->fd[1][1]);
	}
}
