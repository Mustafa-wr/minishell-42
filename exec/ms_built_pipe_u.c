/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_pipe_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:49:41 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 19:15:54 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			unset_cmp(c->m_env, p[i].cmd[j]);
			unset_cmp(c->m_export, p[i].cmd[j]);
		}
		else
		{
			write(2, p[i].cmd[j], ft_strlen(p[i].cmd[j]));
			write (2, " : not a valid identifier\n", 26);
		}
		j++;
	}
	c->env_count -= 1;
}

void	ft_unset(t_cmds *p, int i, int fd, t_pipe *c)
{
	int	j;

	j = 0;
	(void)fd;
	if (p->red_len > 0 && c->cr != 1)
		check_exec_redirect(p, c, 0, 0);
	if (!p[i].cmd[j + 1])
		return ;
	j = 1;
	while (p[i].cmd[j])
	{
		if (ft_isalpha_str(p[i].cmd[j]) == 0)
		{
			unset_cmp(c->m_env, p[i].cmd[j]);
			unset_cmp(c->m_export, p[i].cmd[j]);
		}
		else
		{
			write(2, p[i].cmd[j], ft_strlen(p[i].cmd[j]));
			write (2, " : not a valid identifier\n", 26);
		}
		j++;
	}
	c->env_count -= 1;
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

void	before_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (c->pid == 0)
	{
		if (v->j == 0)
			first_cmd(c, p, v);
		else if (v->j == p->cmd_len - 1)
			third2_cmd(c, p, v);
		else
		{
			if (v->i % 2 == 1)
				fourth_cmd(c, p, v);
			else
				fifth_cmd(c, p, v);
			sixth_cmd(c, p, v);
		}
	}
}