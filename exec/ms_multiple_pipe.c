/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 21:04:43 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	close(c->e_fd);
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	else
		dup2(c->fd[0][1], STDOUT_FILENO);
	if (input_check(p, c, v->j))
		dup2(c->fd[0][1], STDOUT_FILENO);
	if (builtins_pipes(p, c, c->fd[0][1], v->j) == 0)
		free_and_exit(c, p);
	close(c->fd[0][1]);
	close(c->fd[0][0]);
	c->cmd_exec = check_command_existence(p[v->j].cmd[0], c->m_path);
	if (!c->cmd_exec)
		child_exit(p, v->j, c, 0);
	if (execve(c->cmd_exec, p[v->j].cmd, NULL) < 0)
	{
		write(2, p[v->j].cmd[0], ft_strlen(p[v->j].cmd[0]));
		write(2, ": command not found\n", 21);
		free(c->cmd_exec);
		closing_fds(c);
		g_exit_code = 126;
		free_and_exit(c, p);
	}
}

void	second_cmd(t_pipe *c, t_vars *v, t_cmds *p)
{
	if (v->i % 2 == 0 && v->j == 1 && input_check(p, c, v->j) == 0)
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
		{
			printf("error3\n");
			exit(0);
		}
		close(c->fd[0][0]);
		close(c->fd[0][1]);
	}
	else if (v->i % 2 == 1 && input_check(p, c, v->j) == 0)
	{
		dup2(c->fd[0][0], STDIN_FILENO);
		close(c->fd[0][1]);
		close(c->fd[0][0]);
	}
	else
	{
		if (input_check(p, c, v->j) == 0)
			dup2(c->fd[1][0], STDIN_FILENO);
		close(c->fd[1][1]);
		close(c->fd[1][0]);
	}
}

void	third2_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	second_cmd(c, v, p);
	if (builtins_pipes(p, c, 1, v->j) == 0)
		last_exit_e(v, p, c);
	c->cmd_exec = check_command_existence(p[v->j].cmd[0], c->m_path);
	if (!c->cmd_exec)
		child_exit(p, v->j, c, c->e_fd);
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
		ft_putnbr_fd(g_exit_code, c->e_fd);
		close(c->e_fd);
		free_and_exit(c, p);
	}		
}

void	fourth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	if (input_check(p, c, v->j) == 0 && output_check(p, c, v->j) == 0)
	{
		if (input_check(p, c, v->j) == 0)
			dup2(c->fd[0][0], STDIN_FILENO);
		if (output_check(p, c, v->j) == 0)
			dup2(c->fd[1][1], STDOUT_FILENO);
	}
	else
	{
		if (input_check(p, c, v->j) == 0)
			dup2(c->fd[0][0], STDIN_FILENO);
		if (output_check(p, c, v->j) == 0)
		{
			if (dup2(c->fd[1][1], STDOUT_FILENO) == -1)
			{
				printf("error10\n");
				exit(0);
			}
		}
		close(c->fd[0][0]);
		close(c->fd[1][1]);
	}
}

void	multiple_pipes(t_cmds *p, t_pipe *c)
{
	t_vars	v;

	init1(&v, c);
	while (v.j < p->cmd_len)
	{
		if (v.i % 2 == 0 || v.i == 0)
		{
			c->p_f1 = 1;
			pipe(c->fd[0]);
		}
		else if (v.i % 2 == 1)
		{
			c->p_f2 = 1;
			pipe(c->fd[1]);
		}
		if (check_heredoc(p, c) == 1)
			exec_heredoc(p, c, v.j);
		c->pid = fork();
		before_cmd(c, p, &v);
		closing_pipe(c, p, &v);
		v.i++;
		v.j++;
	}
	closing_fds(c);
	wait_pipes(&v, c, p);
}
