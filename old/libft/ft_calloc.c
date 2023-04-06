/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:30:12 by mradwan           #+#    #+#             */
/*   Updated: 2022/07/26 00:23:38 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*i;

	if ((size != 0 && count > SIZE_MAX / size))
		return (NULL);
	i = malloc((count * size));
	if (!i)
		return (NULL);
	ft_bzero(i, (count * size));
	return (i);
}

// int main()
// {
//     int *ptr;
//
//     ptr = ft_calloc (4, sizeof(int));
//     printf ("%s\n", ptr);
//     return (0);
// }
