/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:46:46 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 21:04:56 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing_fds(t_pipe *c)
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

void	ft_unset_p(t_cmds *p, int i, int fd, t_pipe *c)
{
	int	j;

	j = 0;
	(void)fd;
	if (!p[i].cmd[j + 1])
		return ;
	j = 1;
	while (p[i].cmd[j])
	{
		if (ft_isalpha_str(p[i].cmd[j]) == 0)
		{
			unset_cmp(&c->m_env, p[i].cmd[j], c);
			unset_cmp(&c->m_export, p[i].cmd[j], c);
		}
		else
			print_error(i, j, p);
		j++;
	}
	c->env_count -= 1;
}

void	sixth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	close(c->e_fd);
	closing_fds(c);
	if (builtins_pipes(p, c, c->fd[0][1], v->j) == 0)
		free_and_exit(c, p);
	c->cmd_exec = check_command_existence(p[v->j].cmd[0], c->m_path);
	if (!c->cmd_exec)
		child_exit(p, v->j, c, 0);
	if (execve(c->cmd_exec, p[v->j].cmd, NULL) < 0)
	{
		write(2, p[v->j].cmd[0], ft_strlen(p[v->j].cmd[0]));
		write(2, ": command not found\n", 21);
		free(c->cmd_exec);
		g_exit_code = 126;
		free_and_exit(c, p);
	}
}

void	closing_pipe(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (v->i % 2 == 1 && v->i != 0)
	{
		close(c->fd[0][0]);
		close(c->fd[0][1]);
		if (v->j == p->cmd_len - 1)
		{
			close(c->fd[1][1]);
			close(c->fd[1][0]);
		}
		v->i = -1;
		c->p_f1 = 0;
	}
	else if (v->i % 2 == 0 && v->j != 0)
	{
		close(c->fd[1][0]);
		close(c->fd[1][1]);
		v->i = 0;
		c->p_f2 = 0;
	}
}

void	export_last(t_pipe *c, t_cmds *p, int j)
{
	ft_lstadd_back(&c->m_export, ft_lstnew(ft_strdup(p[0].cmd[j])));
	ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
	c->env_count += 1;
}
