/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 14:46:37 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/23 17:37:54 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_undoalloc(char **split, int i)
{
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

static int	ft_worddet(char const *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		if (!quote && s[i] == c && i > 0 && s[i - 1] != c)
			count++;
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		count++;
	return (count);
}

static char	*ft_cpystr(char const *s, char c)
{
	int		i;
	char	*str;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		if (!quote && s[i] == c)
			break ;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	return (ft_memcpy(str, s, i));
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	if (!s)
		return (NULL);
	count = ft_worddet(s, c);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		while (s[j] && (s[j] == c || s[j] == '\t'))
			j++;
		split[i] = ft_cpystr(s + j, c);
		if (!split[i])
			ft_undoalloc(split, i);
		j += ft_strlen(split[i]);
		i++;
	}
	split[i] = NULL;
	return (split);
}
