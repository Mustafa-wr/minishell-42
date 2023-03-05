/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:57:46 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/05 19:44:51 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	c = ft_strlen(dst);
	d = 0;
	while (src[d] != '\0' && c + 1 < dstsize)
	{
		dst[c] = src[d];
		c++;
		d++;
	}
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}

char	*ft_strcat(char *dest, const char *src)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (dest[y] != '\0')
		y++;
	while (src[i] != '\0')
	{
		dest[y] = src[i];
		y++;
		i++;
	}
	dest[y] = src[i];
	return (dest);
}

/*
int main()
{
    char s[] = "as";
    char d[]  = "sfss";
    printf("d: %zu\n", ft_strlcat(d,s, 5));
}
*/