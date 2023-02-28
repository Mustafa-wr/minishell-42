/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:14:04 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/28 21:00:00 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_export(t_pipe *p, char *add)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	int	k = 0;
	tmp2 = NULL;
	tmp = p->m_export;
	tmp3 = tmp;
	// while (p->args[i])
	// {
	// 	j = 0;
	// 	while (p->args[i][j])
	// 	{
	// 		k = 0;
	// 		while(p->args[i][j][k])
	// 		{
	// 			printf("%c", p->args[i][j][k]);
	// 			k++;
	// 		}
	// 		printf("\n");
	// 		j++;
	// 	}
	// 	i++;
	// }
	// i = 0;
	// j = 0;
	// exit(0);
	// exit(0);
	j += 1;
	// printf("s = %s\n", p->args[k][j]);
	// exit(0);
	while (p->args[k][j])
	{
		if (strncmp_orginal(p->args[k][j], "=", 1) != 0)
		{
			tmp = tmp3;
			while (tmp)
			{
				// printf("here0");
				if (strncmp_orginal(tmp->content, p->args[k][j], ft_strlen(tmp->content)) > 0)
				{
					tmp2 = ft_lstnew(add);
					printf("j = %s", tmp2->content);
					tmp2->next = tmp;
					insert_the_node(p, tmp, add, i);
					break ;
				}
				tmp = tmp->next;
				i++;
			}
			if (!tmp)
			{
				ft_lstadd_back(&p->m_export, ft_lstnew(add));
				return ;
			}
			printf("s = %s\n", p->args[k][j]);
		}
		j++;
	}
	// if (!tmp)
	// {
	// 	// printf("hh");
	// 	ft_lstadd_back(&p->m_export, ft_lstnew(add));
	// 	return ;
	// }
	// else if (tmp)
	// {
	// 	// printf("add = %s\n", add);
	// 	ft_lstadd_front(&p->m_export, ft_lstnew(add));
	// 	return ;
	// }
	// i--;
	// tmp = tmp3;
	// while (i > 0)
	// {
	// 	tmp = tmp->next;
	// 	i--;
	// }
	// printf("t = %s", tmp->content);
	// exit(0);
	// tmp->next = tmp2;
	// while (tmp3)
	// {
	// 	printf("tdeclare x %s\n", tmp3->content);
	// 	tmp3 = tmp3->next;
	// }
	// exit(0);
}

void	insert_the_node(t_pipe *p, t_list *tmp, char *add, int i)
{
	t_list	*tmp3;

		printf("entered");
	tmp3 = p->m_export;
	if (!tmp)
	{
		ft_lstadd_back(&p->m_export, ft_lstnew(add));
		return ;
	}
	else if (tmp)
	{
		// printf("add = %s\n", add);
		ft_lstadd_front(&p->m_export, ft_lstnew(add));
		return ;
	}
	printf("here");
	i--;
	tmp = tmp3;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	exit(0);
}