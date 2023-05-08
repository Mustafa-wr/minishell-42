/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:04:59 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/25 14:21:26 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_equal(t_cmds *p, int i, int j)
{
	int		k;

	k = 0;
	while (p[i].cmd[j][k])
	{
		if (p[i].cmd[j][k] == '=')
			return (1);
		k++;
	}
	return (0);
}

void	changing_the_value(t_cmds *p, int i, int j, t_pipe *c)
{
	c->k = 0;
	c->tmpp = c->m_export;
	c->tmp2 = c->tmpp;
	c->tmp3 = NULL;
	while (c->tmpp)
	{
		if (strncmp_orginal(c->tmpp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
			c->tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			c->tmp3->next = c->tmpp->next;
			if (c->tmp2->content != c->tmpp->content)
				c->tmp2->next = c->tmp3;
			break ;
		}
		c->tmp2 = c->tmpp;
		c->tmpp = c->tmpp->next;
		c->k++;
	}
	if (c->tmp2->content != c->tmpp->content)
		c->tmp2->next = c->tmp3;
	free(c->tmpp->content);
	free(c->tmpp);
	if (c->k == 0)
		c->m_export = c->tmp3;
}

char	*env_index(int index, t_list *env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = env;
	while (i < index && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp)
		return (tmp->content);
	else
		return (NULL);
}

void	changing_the_env_v(t_cmds *p, int i, int j, t_pipe *c)
{
	c->k = 0;
	c->tmpp = c->m_env;
	c->tmp2 = c->tmpp;
	c->tmp3 = NULL;
	while (c->tmpp)
	{
		if (strncmp_orginal(c->tmpp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
			c->tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			c->tmp3->next = c->tmpp->next;
			if (c->tmp2->content != c->tmpp->content)
				c->tmp2->next = c->tmp3;
			break ;
		}
		c->tmp2 = c->tmpp;
		c->tmpp = c->tmpp->next;
		c->k++;
	}
	if (c->tmp2->content != c->tmpp->content)
		c->tmp2->next = c->tmp3;
	free(c->tmpp->content);
	free(c->tmpp);
	if (c->k == 0)
		c->m_env = c->tmp3;
}

void	unset_cmp(t_list **lst, char *str, t_pipe *c)
{
	c->tmpp = (*lst);
	c->tmp2 = c->tmpp;
	while (c->tmpp)
	{
		if (strncmp_orginal(c->tmpp->content, str, len_till_equal(str)) == 0)
		{
			if (c->tmp2->content == c->tmpp->content)
				(*lst) = (*lst)->next;
			else if (c->tmpp->next)
			{
				c->tmp3 = c->tmpp->next;
				c->tmp2->next = c->tmp3;
			}
			else
				c->tmp2->next = NULL;
			free(c->tmpp->content);
			free(c->tmpp);
			return ;
		}
		c->tmp2 = c->tmpp;
		c->tmpp = c->tmpp->next;
	}
}
