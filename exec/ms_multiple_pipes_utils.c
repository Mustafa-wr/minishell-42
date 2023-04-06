/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:46:46 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 18:59:11 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing_fds(t_pipe *c)
{
	close(c->fd[0][0]);
	close(c->fd[0][1]);
	close(c->fd[1][0]);
	close(c->fd[1][1]);
}

void	third2_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	second_cmd(c, v, p);
	if (builtins_pipes(p, c, 1, v->j) == 0)
		free_and_exit(c, p);
	c->cmd_exec = check_command_existence(p[v->j].cmd[0], c->m_path);
	if (!c->cmd_exec)
	{
		g_exit_code = 127;
		free_and_exit(c, p);
	}
	else
	{
		close(c->fdin);
		close(c->fdout);
	}
	if (execve(c->cmd_exec, p[v->j].cmd, NULL) < 0)
	{
		write(2, p[v->j].cmd[0], ft_strlen(p[v->j].cmd[0]));
		write(2, ": command not found\n", 21);
		free(c->cmd_exec);
		g_exit_code = 126;
		free_and_exit(c, p);
	}		
}

void	fourth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	else if (input_check(p, c, v->j) == 0)
	{
		dup2(c->fd[0][0], STDIN_FILENO);
		if (dup2(c->fd[1][1], STDOUT_FILENO) == -1)
			exit(0);
	}
	else
	{
		if (input_check(p, c, v->j) == 0)
		{
			dup2(c->fd[0][0], STDIN_FILENO);
			exit(0);
		}
		if (dup2(c->fd[1][1], STDOUT_FILENO) == -1)
			exit(0);
		close(c->fd[0][0]);
		close(c->fd[1][1]);
	}
}

void	fifth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	else
	{
		if (dup2(c->fd[1][0], STDIN_FILENO) == -1)
			exit(0);
		if (dup2(c->fd[0][1], STDOUT_FILENO) == -1)
			exit(0);
	}
}

void	sixth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	closing_fds(c);
	if (builtins_pipes(p, c, c->fd[0][1], v->j) == 0)
		free_and_exit(c, p);
	c->cmd_exec = check_command_existence(p[v->j].cmd[0], c->m_path);
	if (!c->cmd_exec)
	{
		g_exit_code = 127;
		free_and_exit(c, p);
	}
	if (execve(c->cmd_exec, p[v->j].cmd, NULL) < 0)
	{
		write(2, p[v->j].cmd[0], ft_strlen(p[v->j].cmd[0]));
		write(2, ": command not found\n", 21);
		free(c->cmd_exec);
		g_exit_code = 126;
		free_and_exit(c, p);
	}
}