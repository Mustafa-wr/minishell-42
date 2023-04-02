/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redierction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:50:12 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/03 03:26:13 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exec_rederict(t_cmds *p, t_pipe *c, int pm, int j)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	c->fd1 = 0;
	(void)pm;
	while (i < p[j].red_len)
	{
		if (p[j].outs[i].flag == 1)
		{
			// printf("here\n");
			// printf("fd = %s\n", p[j].outs[i].file_name);
			fd = open(p[j].outs[i].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			// printf("fdv = %d\n", fd);
			if (fd < 0)
			{
				perror("open");
				g_exit_code = 1;
				if (pm == 1)
					free_and_exit(c, p);
				else
					return (-1);
			}
		}
		else if (p[j].outs[i].flag == 2)
		{
			fd = open(p[j].outs[i].file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				g_exit_code = 1;
				free_and_exit(c, p);
			}
		}
		if (i == p[j].red_len - 1)
		{
			// write(2, "here\n", 5);
			return (fd);
		}
		if ((p[j].outs[i].flag == 1 && p[j].outs[i + 1].flag != 1) && (p[j].outs[i].flag == 1 && p[j].outs[i + 1].flag != 2))
		{
			// ft_putnbr_fd(i, 2);
			// printf("f = %d\n", p[j].outs[i + 1].flag);
			if (fd == 0)
			{
				// close(fd);
				return (0);
			}
			return (fd);
		}
		i++;
		// if (fd > 2)
			close(fd);
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

int	check_input_redirect(t_cmds *p, t_pipe *c, int pm, int j)
{
	c->i = 0;
	c->fd1 = 0;
	while (c->i < p[j].red_len)
	{
		if (p[j].outs[c->i].flag == 0)
		{
			c->fd1 = open(p[c->j].outs[c->i].file_name, O_RDONLY, 0644);
			if (c->fd1 < 0)
			{
				perror("open");
				g_exit_code = 1;
				if (pm == 1)
					free_and_exit(c, p);
				else
					return (-1);
			}
		}
		if (c->i == p[j].red_len - 1)
			return (c->fd1);
		if (p[j].outs[c->i + 1].flag != 0)
		{
			// printf("here1\n");
			return (heredoc_condition(c->fd1));
		}
		c->i++;
		if (c->fd1 > 2)
		{
			// printf("closed\n");
			close(c->fd1);
		}
	}
	return (0);
}
