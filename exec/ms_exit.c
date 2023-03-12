/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:59 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/12 21:32:24 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list **lst)
{
	t_list	*tmp;

	while ((*lst)->next)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		// if (tmp->content)
		free(tmp->content);
		free(tmp);
	}
	free((*lst)->content);
	free(*lst);
}

void	free_and_exit(t_pipe *c, t_cmds *p)
{
	(void)p;
	free_list(&c->m_env);
	free_list(&c->m_export);
	free_strings(c->tmp_env);
	free_all(c, p);
	exit(0);
}
