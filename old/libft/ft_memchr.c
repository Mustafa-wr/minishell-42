/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:55:06 by mradwan           #+#    #+#             */
/*   Updated: 2022/07/25 23:03:17 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	x;
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	x = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == x)
		{
			return (str + i);
		}
		i++;
	}
	return (NULL);
}
// int main(void)
// {
//   char x[] = {'q', 'w', 'e', 'r', 't', 'i'};

//   char *p = ft_memchr(x, 'e', 6);
//   printf("%c", p[2]);
//   return (0);
// }
