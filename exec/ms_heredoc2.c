/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:58:54 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 20:28:14 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_exec(t_cmds *p, t_vars *v, int i, t_pipe *c)
{
	v->q = ft_strjoin(p[i].outs[v->k].file_name, "\n");
	if (ft_strcmp_heredoc(v->line, v->q) == 0)
	{
		break_condition(p, i, v);
		return (1);
	}
	ft_putstr_fd(v->line, v->tmp, 0);
	write(1, "> ", 2);
	free(v->line);
	v->line = get_next_line(0);
	dollar_expansion(&v->line, c);
	free(v->q);
	if (!v->line)
		return (1);
	return (0);
}

char	*create_file(t_pipe *c)
{
	char		*s;

	s = ft_itoa(c->d_t_m);
	c->d_t_m++;
	return (s);
}
