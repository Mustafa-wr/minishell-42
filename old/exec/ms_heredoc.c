/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:44:06 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 18:38:02 by mradwan          ###   ########.fr       */
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

void	exec_heredoc_u(t_cmds *p, int i, t_vars *v)
{
	write(1, "> ", 2);
	v->line = get_next_line(0);
	while (1)
	{
		v->q = ft_strjoin(p[i].outs[v->h].file_name, "\n");
		if (ft_strcmp_heredoc(v->line, v->q) == 0)
		{
			p[i].outs[v->h].flag = 0;
			free(p[i].outs[v->h].file_name);
			p[i].outs[v->h].file_name = ft_strdup(v->m);
			free(v->q);
			break ;
		}
		ft_putstr_fd(v->line, v->tmpp, 0);
		write(1, "> ", 2);
		free(v->line);
		v->line = get_next_line(0);
		free(v->q);
		if (!v->line)
			break ;
	}
	if (v->line)
		free(v->line);
}

void	exec_h_u(t_vars *v)
{
	if (v->tmpp < 0)
	{
		printf("error\n");
		exit(1);
	}
}

int	exec_heredoc(t_cmds *p, t_pipe *c, int i)
{
	t_vars	v;

	c->fd1 = 0;
	v.q = NULL;
	v.m = "h";
	v.h = 0;
	v.tmpp = 0;
	heredoc_len(c, p);
	signal(SIGINT, hdoc_sigint_handler);
	while (v.h < p[i].red_len)
	{
		if (p[i].outs[v.h].flag == 3)
		{
			v.tmpp = open(v.m, O_RDWR | O_TRUNC | O_CREAT, 0644);
			exec_h_u(&v);
			exec_heredoc_u(p, i, &v);
			if (v.h == p[i].red_len - 1)
				break ;
			close(v.tmpp);
		}
		v.h++;
	}
	close(v.tmpp);
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
