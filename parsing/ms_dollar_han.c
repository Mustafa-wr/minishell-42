/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_han.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:11:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/05 19:47:37 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_substr(char *str, int start, int len, const char *replace)
{
	int		replace_len;
	int		str_len;
	int		new_len;
	char	*new_str;

	replace_len = ft_strlen(replace);
	str_len = ft_strlen(str);
	new_len = str_len - len + replace_len;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, start);
	new_str[start] = '\0';
	ft_strcat(new_str, replace);
	ft_strcat(new_str, &str[start + len]);
	return (new_str);
}

// char	*replace_substr(char *str, int start, int len, const char *replace)
// {
// 	int		replace_len;
// 	int		str_len;
// 	int		new_len;
// 	char	*new_str;

// 	replace_len = strlen(replace);
// 	str_len = strlen(str);
// 	new_len = str_len - len + replace_len;
// 	new_str = malloc(new_len + 1);
// 	if (!new_str)
// 		return (NULL);
// 	strncpy(new_str, str, start);
// 	new_str[start] = '\0';
// 	strcat(new_str, replace);
// 	strcat(new_str, &str[start + len]);
// 	return (new_str);
// }

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
					*str = replace_substr(*str, var.i - len - 1, len + 1, expanded);
					var.i += ft_strlen(expanded) - len - 1;
				}
				free(tmp);
			}
		}
		var.i++;
	}
}
