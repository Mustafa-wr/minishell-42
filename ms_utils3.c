/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:14:04 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/02 21:51:40 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_export(t_cmds *p, t_pipe *c, int i, int j)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;

	int	k = 0;
	tmp2 = NULL;
	tmp = c->m_export;
	tmp3 = tmp;
	if (check_if_exist(p, i, j, c) == 0 && check_for_equal(p, i, j) == 0)
	{
		// printf("sheeeel\n\n");
		return ;
	}
	else if (check_if_exist(p, i, j, c) == 0 && check_for_equal(p, i, j) == 1)
	{
		// printf("hina");
		changing_the_value(p, i, j, c);
		return ;
	}
	if (strncmp_orginal(p[k].cmd[j], "=", 1) != 0)
	{
		while (tmp)
		{
			if (strncmp_orginal(tmp->content, p[k].cmd[j], ft_strlen(tmp->content)) > 0)
			{
				tmp2 = ft_lstnew(p[k].cmd[j]);
				tmp2->next = tmp;
				break ;
			}
			tmp = tmp->next;
			i++;
		}
		if (!tmp)
		{
			ft_lstadd_back(&c->m_export, ft_lstnew(p[k].cmd[j]));
			return ;
		}
		else if (tmp && i == 0)
		{
			ft_lstadd_front(&c->m_export, tmp2);
			return ;
		}
		i--;
		tmp = tmp3;
		while (i - 1 > 0 && tmp->next)
		{
			tmp = tmp->next;
			i--;
		}
		tmp->next = tmp2;
	}
	// return ;
}

void	insert_the_node(t_cmds *p, t_pipe *c)
{
	t_list	*tmp3;
	int		i;
	int		j;

	// printf("entered");
	i = 0;
	j = 1;
	tmp3 = c->m_export;
	while (p[i].cmd[j])
	{
		printf("p = %s\n", p[i].cmd[j]);
		add_to_export(p, c, i, j);
		j++;
	}
}

int	check_if_exist(t_cmds *p, int i, int j, t_pipe *c)
{
	int		counter;
	int		len;
	t_list	*t_e;

	counter = 0;
	// printf("p[i].cmd[j + 1] = %s\n", p->args[i][j]);
	// if (p->args[i][j + 1] == NULL)
	// 	return (1);
	len = len_till_equal(p[i].cmd[j]);
	// printf("len = %d", len);
	t_e = c->m_export;
	while (t_e)
	{
		if (strncmp_orginal(t_e->content, p[i].cmd[j], len) == 0)
		{
			// printf("out\n");
			return (0);
		}
		t_e = t_e->next;
	}
	return (1);
}

int	len_till_equal(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
