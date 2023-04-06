/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:04:59 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 05:52:38 by abdamoha         ###   ########.fr       */
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
	int		k;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;

	k = 0;
	tmp = c->m_export;
	tmp2 = tmp;
	tmp3 = NULL;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
			tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			tmp3->next = tmp->next;
			if (tmp2->content != tmp->content)
				tmp2->next = tmp3;
			break ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
		k++;
	}
	if (tmp2->content != tmp->content)
		tmp2->next = tmp3;
	free(tmp->content);
	free(tmp);
	if (k == 0)
		c->m_export = tmp3;
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
	int		k;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;

	k = 0;
	tmp = c->m_env;
	tmp2 = tmp;
	tmp3 = NULL;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
			tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			tmp3->next = tmp->next;
			if (tmp2->content != tmp->content)
				tmp2->next = tmp3;
			break ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
		k++;
	}
	if (tmp2->content != tmp->content)
		tmp2->next = tmp3;
	if (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
	if (k == 0)
		c->m_export = tmp3;
}

void	unset_cmp(t_list *lst, char *str)
{
	t_list	*tmp3;
	t_list	*tmp2;
	t_list	*tmp;

	tmp = lst;
	tmp2 = tmp;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, str, len_till_equal(str)) == 0)
		{
			tmp3 = tmp->next;
			tmp2->next = tmp3;
			free(tmp->content);
			free(tmp);
			return ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}
