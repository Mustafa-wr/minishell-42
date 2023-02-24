/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:40:34 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/24 21:41:14 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strncmp_orginal(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (ss1[i] != '\0' && ss2[i] != '\0' && i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i != n)
		return (ss1[i] - ss2[i]);
	return (0);
}