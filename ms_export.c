/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:04:59 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/01 21:34:54 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_equal(t_pipe *p, int i, int j)
{
	int		k;

	k = 0;
	while (p->args[i][j][k])
	{
		if (p->args[i][j][k] == '=')
			return (1);
		k++;
	}
	return (0);
}

void	changing_the_value(t_pipe *p, int i, int j)
{
	int		k;
	int		len;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;

	k = 0;
	len = len_till_equal(p, i, j);
	tmp = p->m_export;
	tmp2 = tmp;
	tmp3 = NULL;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, p->args[i][j], len + 1) == 0)
		{
			tmp3 = ft_lstnew(p->args[i][j]);
			tmp3->next = tmp->next;
			// free(tmp->content);
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
	printf("tmp2 = %s", tmp2->content);
	tmp2->next = tmp3;
	// free(tmp2->content);
	// while (tmp3)
	// {
	// 	printf("tmp3 = %s\n", tmp3->content);
	// 	tmp3 = tmp3->next;
	// }
	// exit(0);
	// p->m_export = tmp3;
}
