/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:21:59 by mradwan           #+#    #+#             */
/*   Updated: 2022/07/23 14:57:05 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*x;

	x = (char *)s;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char	bytes[5];
	int		i;

    bytes[5] = {1, 'i', 3, 4,'x'};
    ft_bzero(bytes, 5);
    i = 0;
    while (i < 5)
    {
        printf("%d, ", bytes[i]);
        i++;
    }
    return (0);
}
*/
