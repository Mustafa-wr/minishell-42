/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:04:59 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/12 21:32:28 by abdamoha         ###   ########.fr       */
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
			tmp3 = ft_lstnew(p[i].cmd[j]);
			tmp3->next = tmp->next;
			break ;
		}
		tmp = tmp->next;
		k++;
	}
	while (k - 1 > 0 && tmp2)
	{
		tmp2 = tmp2->next;
		k--;
	}
	tmp2->next = tmp3;
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
			tmp3 = ft_lstnew(p[i].cmd[j]);
			tmp3->next = tmp->next;
			break ;
		}
		tmp = tmp->next;
		k++;
	}
	while (k - 1 > 0 && tmp2)
	{
		tmp2 = tmp2->next;
		k--;
	}
	tmp2->next = tmp3;
}

void	unset_cmp(t_cmds *p, t_list *lst, int i, int j)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, p[i].cmd[j + 1],
				len_till_equal(p[i].cmd[j + 1])) == 0)
		{
			tmp->content = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}
