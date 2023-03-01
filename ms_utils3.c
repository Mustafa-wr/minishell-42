/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:14:04 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/01 19:05:26 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_export(t_pipe *p, char *add, int i, int j)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	int	k = 0;
	tmp2 = NULL;
	tmp = p->m_export;
	tmp3 = tmp;
	(void)add;
	if (check_if_exist(p, i, j) == 0 && check_for_equal(p, i, j) == 0)
	{
		printf("sheeeel\n\n");
		return ;
	}
	else if (check_if_exist(p, i, j) == 0 && check_for_equal(p, i, j) == 1)
	{
		printf("hina");
		changing_the_value(p, i, j);
		return ;
	}
	if (strncmp_orginal(p->args[k][j], "=", 1) != 0)
	{
		while (tmp)
		{
			if (strncmp_orginal(tmp->content, p->args[k][j], ft_strlen(tmp->content)) > 0)
			{
				tmp2 = ft_lstnew(p->args[k][j]);
				tmp2->next = tmp;
				break ;
			}
			tmp = tmp->next;
			i++;
		}
		if (!tmp)
		{
			ft_lstadd_back(&p->m_export, ft_lstnew(p->args[k][j]));
			return ;
		}
		else if (tmp && i == 0)
		{
			ft_lstadd_front(&p->m_export, tmp2);
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

void	insert_the_node(t_pipe *p, t_list *tmp, t_list *tmp2)
{
	t_list	*tmp3;
	int		i;
	int		j;

	(void)tmp;
	(void)tmp2;
	// printf("entered");
	i = 0;
	j = 1;
	tmp3 = p->m_export;
	while (p->args[i][j])
	{
		printf("p = %s\n", p->args[i][j]);
		add_to_export(p, NULL, i, j);
		j++;
	}
}

int	check_if_exist(t_pipe *p, int i, int j)
{
	int		counter;
	int		len;
	t_list	*t_e;

	counter = 0;
	printf("p->args[i][j + 1] = %s\n", p->args[i][j]);
	// if (p->args[i][j + 1] == NULL)
	// 	return (1);
	len = len_till_equal(p, i, j);
	printf("len = %d", len);
	t_e = p->m_export;
	while (t_e)
	{
		if (strncmp_orginal(t_e->content, p->args[i][j], len) == 0)
		{
			printf("out\n");
			return (0);
		}
		t_e = t_e->next;
	}
	return (1);
}

int	len_till_equal(t_pipe *p, int i, int j)
{
	int		k;

	k = 0;
	while (p->args[i][j][k] != '=' && p->args[i][j][k])
		k++;
	return (k);
}
