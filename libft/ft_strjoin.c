/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:02 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/10 16:38:14 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		len1;
// 	int		len2;
// 	char	*str;

// 	if (s1 != NULL && s2 != NULL)
// 	{
// 		len1 = ft_strlen(s1);
// 		len2 = ft_strlen(s2);
// 		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
// 		if (str == NULL)
// 			return (NULL);
// 		i = -1;
// 		while (s1[++i])
// 			str[i] = s1[i];
// 		i = -1;
// 		while (s2[++i])
// 		{
// 			str[len1] = s2[i];
// 			len1++;
// 		}
// 		str[len1] = '\0';
// 		return (str);
// 	}
// 	return (NULL);
// }

static void	mu(char *str, char const *s2, int i)
{
	int	n;

	n = 0;
	while (s2[n] != '\0')
	{
		str[i] = s2[n];
		i++;
		n++;
	}
	str[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		str = malloc(sizeof(char) * len + 1);
		if (!str)
			return (NULL);
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		mu(str, s2, i);
		return (str);
	}
	return (0);
}

/*
int	main(void)
{
	printf("%s", ft_strjoin("hello", " hb"));
}
*/
