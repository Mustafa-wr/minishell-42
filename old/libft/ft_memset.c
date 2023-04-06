/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:02:26 by mradwan           #+#    #+#             */
/*   Updated: 2022/07/18 13:09:29 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*x;

	x = (char *)b;
	i = 0;
	while (i < len)
	{
		x[i] = c;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	char	c[] = "qwertyuiop";

// 	printf("%s", ft_memset(c, 'A', 3));
// 	return (0);
// }