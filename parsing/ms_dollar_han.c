/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_han.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:11:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/13 16:19:01 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*storing(char *str, int start, int len, char *replace)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str || start + len > (int)ft_strlen(str))
		return (NULL);
	new_str = malloc(sizeof(char) * \
		(ft_strlen(str) - len + ft_strlen(replace) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		new_str[j++] = str[i++];
	while (*replace)
		new_str[j++] = *replace++;
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

void	quotes_check(char **str, t_vars *var)
{
	if ((*str)[var->i] == '\"')
	{
		if (!var->in_d_quotes)
			var->in_d_quotes = 1;
		else if (var->in_d_quotes)
			var->in_d_quotes = 0;
	}
	if ((*str)[var->i] == '\'' && !var->in_d_quotes)
	{
		if (!var->in_quotes)
			var->in_quotes = 1;
		else if (var->in_quotes)
			var->in_quotes = 0;
	}
}

int	expand(char **str, char *expanded, t_vars *var)
{
	expanded = NULL;
	var->i++;
	if ((*str)[var->i] == '?' && (*str)[var->i - 1] == '$')
	{
		expanded = ft_itoa(g_exit_code);
		*str = storing(*str, var->i - 1, 2, expanded);
		var->i += ft_strlen(expanded) - 2;
		free(expanded);
		return (1);
	}
	if (!ft_isalpha((*str)[var->i]) && (*str)[var->i] != '_')
		return (1);
	var->len = 0;
	while (ft_isalnum((*str)[var->i]) || (*str)[var->i] == '_')
	{
		var->len++;
		var->i++;
	}
	return (0);
}

void	generate_strings_helper(char **str, char *expanded, t_vars *var)
{
	char	*joined;
	char	*joined2;

	if (!var->in_d_quotes)
	{
		joined = ft_strjoin(expanded, "\"");
		joined2 = ft_strjoin("\"", joined);
		*str = storing(*str, var->i - var->len - 1, var->len + 1, joined2);
		var->i += ft_strlen(expanded) - var->len - 1;
		free(joined2);
		free(joined);
	}
	else
	{
		*str = storing(*str, var->i - var->len - 1, var->len + 1, expanded);
		var->i += ft_strlen(expanded) - var->len - 1;
	}
}

int	generate_string(char **str, char **tmp, t_vars *var, t_pipe *pipe)
{
	// char	*joined;
	// char	*joined2;
	char	*expanded;

	expanded = NULL;
	if (*tmp)
	{
		expanded = my_getenv(*tmp, pipe);
		if (expanded)
		{
			generate_strings_helper(str, expanded, var);
			// if (!var->in_d_quotes)
			// {
			// 	joined = ft_strjoin(expanded, "\"");
			// 	joined2 = ft_strjoin("\"", joined);
			// 	*str = storing(*str, var->i - var->len - 1, var->len + 1, joined2);
			// 	var->i += ft_strlen(expanded) - var->len - 1;
			// 	free(joined2);
			// 	free(joined);
			// }
			// else
			// {
			// 	*str = storing(*str, var->i - var->len - 1, var->len + 1, expanded);
			// 	var->i += ft_strlen(expanded) - var->len - 1;
			// }
		}
		else if (!expanded)
		{
			*str = storing(*str, var->i - var->len - 1, var->len + 1, "");
			var->i -= var->len + 1;
		}
		free(*tmp);
		return (1);
	}
	return (0);
}

void	dollar_expansion(char **str, t_pipe *pipe)
{
	t_vars	var;
	char	*tmp;
	char	*expanded;

	var.len = 0;
	expanded = NULL;
	var.i = 0;
	var.in_d_quotes = 0;
	var.in_quotes = 0;
	while ((*str)[var.i])
	{
		quotes_check(str, &var);
		if ((*str)[var.i] == '$' && !var.in_quotes && (*str)[var.i + 1])
		{
			if (expand(str, expanded, &var))
				continue ;
			tmp = ft_substr(*str, var.i - var.len, var.len);
			if (generate_string(str, &tmp, &var, pipe))
				continue ;
		}
		var.i++;
	}
}
