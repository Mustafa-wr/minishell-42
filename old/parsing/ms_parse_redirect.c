/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:53:42 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 19:32:57 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirect(char **str, t_vars *v)
{
	if ((*str)[v->i] == '>' || (*str)[v->i] == '<')
	{
		v->i++;
		if (((*str)[v->i] == '<' && \
			(*str)[v->i - 1] == '<') \
			|| ((*str)[v->i] == '>' && \
				(*str)[v->i - 1] == '>'))
			v->i++;
		while ((*str)[v->i] == ' ' || (*str)[v->i] == '\t')
			v->i++;
		if (((*str)[v->i] == '>' || (*str)[v->i] == '<') \
			&& (!v->in_quotes))
			return (0);
		while ((*str)[v->i] == ' ' || (*str)[v->i] == '\t')
			v->i++;
		if ((*str)[v->i] == '\0' || ((*str)[v->i] == '|' && !v->in_quotes))
			return (0);
	}
	else
		v->i++;
	return (1);
}

static int	check_from_back(char *s)
{
	int	i;

	i = ft_strlen(s);
	if (i)
		i--;
	while ((s[i] == ' ' || s[i] == '\t') && i > 0)
		i--;
	if (s[i] == '>' || s[i] == '<')
		return (0);
	return (1);
}

static int	redirect_helper(char **str, t_vars *vars)
{
	if (!check_from_back(*str))
		return (0);
	vars->i = 0;
	while ((*str)[vars->i])
	{
		if ((*str)[vars->i] == '\'' || \
			(*str)[vars->i] == '\"')
		{
			if (!vars->in_quotes)
				vars->in_quotes = (*str)[vars->i];
			else if (vars->in_quotes == (*str)[vars->i])
				vars->in_quotes = 0;
		}
		if (!is_redirect(str, vars))
			return (0);
	}
	return (1);
}

int	check_redirect(char *str)
{
	t_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.in_d_quotes = 0;
	vars.in_quotes = 0;
	if (!redirect_helper(&str, &vars))
		return (0);
	return (1);
}
