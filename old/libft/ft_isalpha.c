/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:11:23 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 19:23:48 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha_str(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
