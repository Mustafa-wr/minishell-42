/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:11:21 by mradwan           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/02 18:10:35 by abdamoha         ###   ########.fr       */
=======
/*   Updated: 2023/02/25 23:52:42 by abdamoha         ###   ########.fr       */
>>>>>>> e9c7e44755aaf7c7d479131a17b1a69d194f0a36
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
<<<<<<< HEAD
}
=======
}
>>>>>>> e9c7e44755aaf7c7d479131a17b1a69d194f0a36
