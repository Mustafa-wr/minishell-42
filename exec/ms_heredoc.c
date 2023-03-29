/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:44:06 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/29 21:39:48 by abdamoha         ###   ########.fr       */
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
			{
				printf("heredoc\n");
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

int	exec_heredoc(t_cmds *p, t_pipe *c, int i)
{
	// int	i = 0;
	// int	len = 0;
	int		k = 0;
	int		tmp = 0;
	char	*line;
	// char	*s;

	(void)p;
	c->fd1 = 0;
	// m = c->tmpfile;
	char *m = "h";
	// printf("m = %s\n", m);
	heredoc_len(c, p);
	// printf("cmd  = %s\n", p[i].cmd[0]);
	// printf("del  = %s\n", p[i].outs[0].file_name);
	// s = p[0].outs[k].file_name;
	// printf("s = %s\n", s);
	// usleep(111);
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
			// printf("tmp = %d\n", tmp);
			write(1, "> ", 2);
			line = get_next_line(0);
			while (1)
			{
				if(strcmp(line, ft_strjoin(p[i].outs[k].file_name, "\n")) == 0)
				{
					p[i].outs[k].flag = 0;
					// printf("fn before = %s\n", p[i].outs[k].file_name);
					p[i].outs[k].file_name = ft_strdup(m);
					// printf("fn = %s\n", p[i].outs[k].file_name);
					// printf("flag = %d\n", p[i].outs[k].flag);
					break ;
				}
				ft_putstr_fd(line, tmp, 0);
				write(1, "> ", 2);
				free(line);
				line = get_next_line(0);
				if (!line)
					break ;
			}
			if (line)
				free(line);
			if (k == p[i].red_len - 1)
				break ;
			k++;
			close(tmp);
		}
	}
	close(tmp);
	// tmp = open (m, O_RDONLY, 0644);
	return (0);
	// }
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
			if (p[j].outs[i].flag == 3)
			{
				// printf("name %s\n", p[j].outs[i].file_name);
				fd = open(s, O_RDONLY | O_CREAT, 0644);
				if (fd < 0)
				{
					perror("no such file or dir\n");
					free_and_exit(c, p);
				}
			}
			if (p[j].outs[i + 1].flag != 0)
			{
				printf("p stdin = %s\n", p[j].outs[i].file_name);
				if (fd == 0)
				{
					close(fd);
					return (0);
				}
				return (fd);
			}
			i++;
			close(fd);
		}
		j++;
	}
	return (0);
}