/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_han.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:11:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/07 19:00:39 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	*storing(char *str, int start, int len, const char *replace)
// {
// 	int		replace_len;
// 	int		str_len;
// 	int		new_len;
// 	char	*new_str;

// 	replace_len = ft_strlen(replace);
// 	str_len = ft_strlen(str);
// 	new_len = str_len - len + replace_len;
// 	new_str = malloc(new_len + 1);
// 	if (!new_str || !str)
// 		return (NULL);
// 	ft_strlcpy(new_str, str, start + 1);
// 	ft_strlcat(new_str, replace, new_len + 1);
// 	ft_strlcat(new_str, &str[start + len], new_len + 1);
// 	free(str);
// 	return (new_str);
// }

char	*storing(char *str, int start, int len, char *replace)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str || start + len > (int)ft_strlen(str))
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len + ft_strlen(replace) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	while (*replace)
	{
		new_str[j] = *replace;
		j++;
		replace++;
	}
	while (str[i + len])
	{
		new_str[j] = str[i + len];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	dollar_expansion(char **str)
{
	t_vars	var;
	char	*tmp;
	char	*expanded;
	size_t	len;

	var.i = 0;
	var.in_d_quotes = 0;
	var.in_quotes = 0;
	while ((*str)[var.i])
	{
		if ((*str)[var.i] == '\"')
		{
			if (!var.in_d_quotes)
				var.in_d_quotes = 1;
			else if (var.in_d_quotes)
				var.in_d_quotes = 0;
		}
		if ((*str)[var.i] == '\'' && !var.in_d_quotes)
		{
			if (!var.in_quotes)
				var.in_quotes = 1;
			else if (var.in_quotes)
				var.in_quotes = 0;
		}
		if ((*str)[var.i] == '$' && !var.in_quotes && (*str)[var.i + 1])
		{
			var.i++;
			if ((*str)[var.i] == '?' && var.i == 1 && (*str)[var.i - 1] == '$')
			{
				expanded = ft_itoa(g_exit_code);
				*str = storing(*str, var.i - 1, 2, expanded);
				var.i += ft_strlen(expanded) - 2;
				free(expanded);
				continue ;
			}
			if (!ft_isalpha((*str)[var.i]) && (*str)[var.i] != '_')
				continue ;
			len = 0;
			while (ft_isalnum((*str)[var.i]) || (*str)[var.i] == '_')
			{
				len++;
				var.i++;
			}
			tmp = ft_substr(*str, var.i - len, len);
			if (tmp)
			{
				expanded = getenv(tmp);
				if (expanded)
				{
					*str = storing(*str, var.i - len - 1, len + 1, expanded);
					var.i += ft_strlen(expanded) - len - 1;
				}
				else if (!expanded)
				{
					*str = storing(*str, var.i - len - 1, len + 1, "");
					var.i -= len + 1;
				}
				free(tmp);
				continue ;
			}
		}
		var.i++;
	}
}
