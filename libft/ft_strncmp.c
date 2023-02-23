/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:44:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/23 21:46:43 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
// {
// 	unsigned int	i;
// 	unsigned char	*ss1;
// 	unsigned char	*ss2;

// 	ss1 = (unsigned char *)s1;
// 	ss2 = (unsigned char *)s2;
// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	while (ss1[i] != '\0' && ss2[i] != '\0' && i < n)
// 	{
// 		if (ss1[i] != ss2[i])
// 			return (ss1[i] - ss2[i]);
// 		i++;
// 	}
// 	if (i != n)
// 		return (ss1[i] - ss2[i]);
// 	return (0);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				c;
	int				k;
	unsigned char	*ns1;
	unsigned char	*ns2;

	if (!*s1 || !*s2)
		return (1);
	ns1 = (unsigned char *)s1;
	ns2 = (unsigned char *)s2;
	i = 0;
	c = ft_strlen(s1) - 1;
	k = ft_strlen(s2) - 1;
	while (i < n && c >= 0 && k >= 0)
	{
		if (ns1[c] != ns2[k])
			return (ns1[c] - ns2[k]);
		i++;
		c--;
		k--;
	}
	if (i != n)
		return (ns1[c] - ns2[k]);
	return (0);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
// 		i++;
// 	return (s1[i] - s2[i]);
// }

// int	main(void)
// {
// 	char	*s;
// 	char	*s2;

// 	s = "mk1L";
// 	s2 = "mk1l";
// 	printf("%d", ft_strncmp(s, s2, 4));
// 	return (0);
// }
