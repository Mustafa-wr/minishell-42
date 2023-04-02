/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:32:17 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/01 23:29:00 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isexportable(char *str, int len)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] && i < len)
		{
			if (((ft_isalpha(str[i]) == 0) && str[i] != '_')
			|| str[i] == '-' || str[i] == '+' || (str[0] >= '0' && str[0] <= '9'))
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