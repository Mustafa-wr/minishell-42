/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 19:16:08 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
		check_exec_redirect(p, c, 1, v->j);
	if (builtins_pipes(p, c, c->fd[0][1], v->j) == 0)
		free_and_exit(c, p);
	if (dup2(c->fd[0][1], STDOUT_FILENO) == -1)
		printf("error1\n");
	close(c->fd[0][1]);
	close(c->fd[0][0]);
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

void	second_cmd(t_pipe *c, t_vars *v, t_cmds *p)
{
	if (v->i % 2 == 0 && v->j == 1 && input_check(p, c, v->j) == 0)
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
			exit(0);
		close(c->fd[0][0]);
		close(c->fd[0][1]);
	}
	else if (v->i % 2 == 1 && input_check(p, c, v->j) == 0)
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
			exit(0);
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

void	init1(t_vars *v)
{
	v->i = 0;
	v->j = 0;
	v->h = 0;
	v->i = 0;
}

void	m_pp(t_cmds *p, t_pipe *c, t_vars *v)
{
	if (v->i % 2 == 0 || v->i == 0)
	{
		c->p_f1 = 1;
		pipe(c->fd[0]);
	}
	else if (v->i % 2 == 1)
	{
		c->p_f2 = 1;
		pipe(c->fd[1]);
	}
	if (check_heredoc(p, c) == 1)
		exec_heredoc(p, c, v->j);
}

void	multiple_pipes(t_cmds *p, t_pipe *c)
{
	t_vars	v;

	init1(&v);
	c->cmd_exec = NULL;
	c->cr = 1;
	while (v.j < p->cmd_len)
	{
		m_pp(p, c, &v);
		c->pid = fork();
		before_cmd(c, p, &v);
		closing_pipe(c, p, &v);
		v.i++;
		v.j++;
	}
	v.h = 0;
	closing_fds(c);
	while (v.h < p->cmd_len)
	{
		wait(NULL);
		v.h++;
	}
	c->cr = 0;
	c->p_f1 = 0;
	c->p_f2 = 0;
}
