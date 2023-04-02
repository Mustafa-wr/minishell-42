/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redierction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:50:12 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/02 03:09:56 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exec_rederict(t_cmds *p, t_pipe *c)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	int j = 0;
	c->fd1 = 0;
	while (j < p->cmd_len)
	{
		i = 0;
		while (i < p[j].red_len)
		{
			if (p[j].outs[i].flag == 1)
			{
				fd = open(p[j].outs[i].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					perror("open");
					free_and_exit(c, p);
				}
			}
			else if (p[j].outs[i].flag == 2)
			{
				fd = open(p[j].outs[i].file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0)
				{
					perror("open");
					free_and_exit(c, p);
				}
			}
			if (i == p[j].red_len - 1 && fd > 2)
				return (fd);
			if (p[j].outs[i].flag == 1 && (p[j].outs[i + 1].flag != 1 || p[j].outs[i + 1].flag != 2))
			{
				if (fd == 0)
				{
					close(fd);
					return (0);
				}
				return (fd);
			}
			i++;
			if (fd > 2)
				close(fd);
		}
		j++;
	}
	return (0);
}

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

int	check_input_redirect(t_cmds *p, t_pipe *c)
{
	c->i = 0;
	c->j = 0;
	c->fd1 = 0;
	while (c->j < p->cmd_len)
	{
		c->i = 0;
		while (c->i < p[c->j].red_len)
		{
			if (p[c->j].outs[c->i].flag == 0)
			{
				c->fd1 = open(p[c->j].outs[c->i].file_name, O_RDONLY, 0644);
				if (c->fd1 < 0)
				{
					perror("open");
					g_exit_code = 1;
					free_and_exit(c, p);
				}
			}
			if (c->i == p[c->j].red_len - 1 && c->fd1 > 2)
				return (c->fd1);
			if (p[c->j].outs[c->i + 1].flag != 0)
				return (heredoc_condition(c->fd1));
			c->i++;
			if (c->fd1 > 2)
				close(c->fd1);
		}
		c->j++;
	}
	return (0);
}
