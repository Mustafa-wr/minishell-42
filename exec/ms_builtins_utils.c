/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:20:21 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/11 02:39:32 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_executable(t_pipe *c, t_cmds *p)
{
	int		i;

	i = 0;
	if (ft_strchr(p[i].cmd[0], '.') && ft_strchr(p[i].cmd[0], '/'))
	{
		if (ft_strncmp(p[i].cmd[0], "./minishell", 11) == 0)
		{
			change_shlv(p, c, c->m_env);
			change_shlv(p, c, c->m_export);
			free_all(c, p);
			return (1);
		}
	}
	return (0);
}

static void	shlvl_exec(t_pipe *c, char *s)
{
	s = ft_itoa(increase_shlvl_value(c->tmpp->content));
	c->tmp3 = ft_lstnew(ft_strjoin("SHLVL=", s));
	c->tmp3->next = c->tmpp->next;
	c->tmp2->next = c->tmp3;
	free(c->tmpp->content);
	free(c->tmpp);
}

void	change_shlv(t_cmds *p, t_pipe *c, t_list *lst)
{
	char	*s;

	c->k = 0;
	s = NULL;
	c->tmpp = lst;
	c->tmp2 = c->tmpp;
	c->tmp3 = NULL;
	(void)p;
	(void)c;
	while (c->tmpp)
	{
		if (strncmp_orginal(c->tmpp->content, "SHLVL=",
				len_till_equal("SHLVL=")) == 0)
		{
			shlvl_exec(c, s);
			break ;
		}
		c->tmp2 = c->tmpp;
		c->tmpp = c->tmpp->next;
		c->k++;
	}
	if (s)
		free(s);
}

int	increase_shlvl_value(char *str)
{
	int	i;

	i = len_till_equal(str) + 1;
	return (ft_atoi(str + i) + 1);
}

void	get_path(char **str, t_pipe *c)
{
	char	*s;
	int		i;

	i = 0;
	s = NULL;
	while (str[i])
	{
		if (strncmp_orginal("PATH=", str[i], 5) == 0)
		{
			s = str[i] + 5;
			c->m_path = ft_split(s, ':');
			return ;
		}
		i++;
	}
	return ;
}
