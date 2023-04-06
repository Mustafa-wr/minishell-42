/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:32:17 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 05:39:43 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isexportable(char *str, int len)
{
	int		i;

	i = 0;
	(void)len;
	if (str)
	{
		if (ft_isdigit(str[0]) || (!ft_isalpha(str[0]) && str[0] != '_'))
			return (1);
		i++;
		while (str[i] && i < len)
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	ft_isdigit(int f)
{
	return ((f >= '0' && f <= '9'));
}