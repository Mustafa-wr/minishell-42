/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:44:06 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 20:31:45 by abdamoha         ###   ########.fr       */
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

static int	open_file(t_vars *v, t_pipe *c, t_cmds *p)
{
	v->m = create_file(c);
	v->tmp = open(v->m, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (v->tmp < 0)
	{
		free(v->m);
		c->d_t_m = c->d_t_m * 2 + 1;
		v->m = create_file(c);
		v->tmp = open(v->m, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (v->tmp < 0)
		{
			free(v->m);
			free_all(c, p);
			return (1);
		}
	}
	return (0);
}

void	break_condition(t_cmds *p, int i, t_vars *v)
{
	p[i].outs[v->k].flag = 0;
	free(p[i].outs[v->k].file_name);
	p[i].outs[v->k].file_name = v->m;
	free(v->q);
}

static void	init_heredoc(t_pipe *c, t_vars *v)
{
	c->fd1 = 0;
	v->q = NULL;
	v->m = NULL;
	v->k = -1;
	c->d_t_m = 0;
	v->tmp = 0;
}

int	exec_heredoc(t_cmds *p, t_pipe *c, int i)
{
	t_vars	v;

	init_heredoc(c, &v);
	while (++v.k < p[i].red_len)
	{
		if (p[i].outs[v.k].flag == 3)
		{
			signal(SIGINT, SIG_IGN);
			if (open_file(&v, c, p) == 1)
				return (0);
			write(1, "> ", 2);
			v.line = get_next_line(0);
			if (!v.line)
				return (free(v.m), close(v.tmp), 1);
			dollar_expansion(&v.line, c);
			loop_heredoc(c, p, &v, i);
			if (v.k == p[i].red_len - 1)
				break ;
			if (v.tmp > 2)
				close(v.tmp);
		}
	}
	if (v.tmp > 2)
		close(v.tmp);
	return (0);
}

// void	heredoc_len(t_pipe *c, t_cmds *p)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	c->heredoc_len = 0;
// 	while (i < p->cmd_len)
// 	{
// 		j = 0;
// 		while (j < p[i].red_len)
// 		{
// 			if (p[i].outs[j].flag == 3)
// 				c->heredoc_len++;
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int	heredoc_redierction(t_cmds *p, t_pipe *c, char *s)
// {
// 	c->i = 0;
// 	c->j = 0;
// 	while (c->j < p->cmd_len)
// 	{
// 		c->i = 0;
// 		while (c->i < p[c->j].red_len)
// 		{
// 			if (p[c->j].outs[c->i].flag == 3)
// 			{
// 				c->fd1 = open(s, O_RDONLY | O_CREAT, 0644);
// 				if (c->fd1 < 0)
// 				{
// 					perror("no such file or dir\n");
// 					free_and_exit(c, p);
// 				}
// 			}
// 			if (p[c->j].outs[c->i + 1].flag != 0)
// 				return (heredoc_condition(c->fd1));
// 			c->i++;
// 			close(c->fd1);
// 		}
// 		c->j++;
// 	}
// 	return (0);
// }
