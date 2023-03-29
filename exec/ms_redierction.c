/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redierction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:50:12 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/29 18:09:14 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exec_rederict(t_cmds *p, t_pipe *c)
{
	int		i;
	int		fd;

	i = 0;
	int j = 0;
	c->fd1 = 0;
	while (j < p->cmd_len)
	{
		i = 0;
		while (i < p[j].red_len)
		{
			if (p[j].outs[i].flag == 1)
			{
				fd = open(p[j].outs[i].file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					perror("open");
					return (0);
				}
			}
			if (p[j].outs[i].flag == 1)
			{
				if (i == p[j].red_len - 1)
				{
					printf("p in = %s\n", p[j].outs[i].file_name);
					if (fd == 0)
					{
						close(fd);
						return (0);
					}
					return (fd);
				}
			}
			i++;
			if (fd != 0)
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
	int		i;
	int		fd;

	i = 0;
	int j = 0;
	c->fd1 = 0;
	// printf("cmd_red = %d\n", p->cmd_len);
	while (j < p->cmd_len)
	{
		i = 0;
		while (i < p[j].red_len)
		{
			// printf("red in = %s\n", p[j].outs[i].file_name);
			// printf("flag = %d\n", p[j].outs[i].flag);
			if (p[j].outs[i].flag == 0)
			{
				// printf("name %s\n", p[j].outs[i].file_name);
				fd = open(p[j].outs[i].file_name, O_RDONLY, 0644);
				if (fd < 0)
				{
					perror("no such file or dir\n");
					free_and_exit(c, p);
				}
			}
			if (p[j].outs[i].flag == 0)
			{
				// printf("p stdin = %s\n", p[j].outs[i].file_name);
				if (i == p[j].red_len - 1)
				{
					if (fd == 0)
					{
						printf("close\n");
						close(fd);
						return (0);
					}
					return (fd);
				}
			}
			i++;
			close(fd);
		}
		j++;
	}
	return (0);
}