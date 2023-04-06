/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redierction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:50:12 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 19:14:06 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_fd(t_cmds *p, int x, int y, t_pipe *c)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (p[x].cmd[y])
	{
		i = 0;
		if (k != 0)
			write(c->fd1, " ", 1);
		while (p[x].cmd[y][i])
		{
			write(c->fd1, &p[x].cmd[y][i], 1);
			i++;
		}
		y++;
		k++;
	}
}

int	check_exec_redirect(t_cmds *p, t_pipe *c, int pm, int j)
{
	c->i = 0;
	c->fd1 = 0;
	while (c->i < p[j].red_len)
	{
		if (p[j].outs[c->i].flag == 0)
		{
			c->fd1 = open(p[j].outs[c->i].file_name, O_RDONLY, 0644);
			if (c->fd1 < 0)
			{
				perror("open");
				g_exit_code = 1;
				if (pm == 1 && c->ch != 1)
					free_and_exit(c, p);
				else if (c->ch == 1)
					exit_once(p, c);
				else
					return (-1);
			}
			dup2(c->fd1, STDIN_FILENO);
		}
		else if (p[j].outs[c->i].flag == 1)
		{
			c->fd1 = open(p[j].outs[c->i].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (c->fd1 < 0)
			{
				perror("open");
				g_exit_code = 1;
				if (pm == 1 && c->ch != 1)
					free_and_exit(c, p);
				else if (c->ch == 1)
					exit_once(p, c);
				else
					return (-1);
			}
			dup2(c->fd1, STDOUT_FILENO);
		}
		else if (p[j].outs[c->i].flag == 2)
		{
			c->fd1 = open(p[j].outs[c->i].file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (c->fd1 < 0)
			{
				perror("open");
				g_exit_code = 1;
				if (pm == 1 && c->ch != 1)
					free_and_exit(c, p);
				else if (c->ch == 1)
					exit_once(p, c);
				else
					return (-1);
			}
			dup2(c->fd1, STDOUT_FILENO);
		}
		if (c->fd1 > 2)
			close(c->fd1);
		c->i++;
	}
	return (0);
}
