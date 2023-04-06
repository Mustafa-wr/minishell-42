/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:44:06 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 07:28:12 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_heredoc(t_cmds *p, t_pipe *c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	c->fd1 = 0;
	while (j < p->cmd_len)
	{
		i = 0;
		while (i < p[j].red_len)
		{
			if (p[j].outs[i].flag == 3)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	exec_heredoc(t_cmds *p, t_pipe *c, int i)
{
	int		k;
	int		tmp;
	char	*line;
	char	*m;
	char	*q;

	c->fd1 = 0;
	q = NULL;
	m = "h";
	k = 0;
	tmp = 0;
	heredoc_len(c, p);
	while (k < p[i].red_len)
	{
		if (p[i].outs[k].flag == 3)
		{
			tmp = open(m, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (tmp < 0)
			{
				printf("error\n");
				exit(1);
			}
			write(1, "> ", 2);
			line = get_next_line(0);
			while (1)
			{
				q = ft_strjoin(p[i].outs[k].file_name, "\n");
				if (ft_strcmp_heredoc(line, q) == 0)
				{
					p[i].outs[k].flag = 0;
					free(p[i].outs[k].file_name);
					p[i].outs[k].file_name = ft_strdup(m);
					free(q);
					break ;
				}
				ft_putstr_fd(line, tmp, 0);
				write(1, "> ", 2);
				free(line);
				line = get_next_line(0);
				free(q);
				if (!line)
					break ;
			}
			if (line)
				free(line);
			if (k == p[i].red_len - 1)
				break ;
			close(tmp);
		}
		k++;
	}
	close(tmp);
	return (0);
}

void	heredoc_len(t_pipe *c, t_cmds *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	c->heredoc_len = 0;
	while (i < p->cmd_len)
	{
		j = 0;
		while (j < p[i].red_len)
		{
			if (p[i].outs[j].flag == 3)
				c->heredoc_len++;
			j++;
		}
		i++;
	}
}

int	heredoc_redierction(t_cmds *p, t_pipe *c, char *s)
{
	c->i = 0;
	c->j = 0;
	while (c->j < p->cmd_len)
	{
		c->i = 0;
		while (c->i < p[c->j].red_len)
		{
			if (p[c->j].outs[c->i].flag == 3)
			{
				c->fd1 = open(s, O_RDONLY | O_CREAT, 0644);
				if (c->fd1 < 0)
				{
					perror("no such file or dir\n");
					free_and_exit(c, p);
				}
			}
			if (p[c->j].outs[c->i + 1].flag != 0)
				return (heredoc_condition(c->fd1));
			c->i++;
			close(c->fd1);
		}
		c->j++;
	}
	return (0);
}
