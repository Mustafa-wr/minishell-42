/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:46:03 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/04 19:07:27 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_spaes(int *j, char **new_str, int var)
{
	(*new_str)[(*j)++] = ' ';
	if (var == 0)
		(*new_str)[(*j)++] = '<';
	else if (var == 1)
	{
		(*new_str)[(*j)++] = '<';
		(*new_str)[(*j)++] = '<';
	}
	else if (var == 2)
		(*new_str)[(*j)++] = '>';
	else if (var == 3)
	{
		(*new_str)[(*j)++] = '>';
		(*new_str)[(*j)++] = '>';
	}
	else if (var == 4)
		(*new_str)[(*j)++] = ' ';
	(*new_str)[(*j)++] = ' ';
}

static void	add_spaces_helper(char **str, int *i, int *j, char **new_str)
{
	if ((*str)[*i] == '<' && (*str)[*i + 1] != '<')
		add_spaes(j, new_str, 0);
	else if ((*str)[*i] == '<' && (*str)[*i + 1] == '<')
	{
		(*i)++;
		add_spaes(j, new_str, 1);
	}
	else if ((*str)[*i] == '>' && (*str)[*i + 1] != '>')
		add_spaes(j, new_str, 2);
	else if ((*str)[*i] == '>' && (*str)[*i + 1] == '>')
	{
		(*i)++;
		add_spaes(j, new_str, 3);
	}
	else if ((*str)[*i] == '\t')
		add_spaes(j, new_str, 4);
	else
		(*new_str)[(*j)++] = (*str)[(*i)];
}

char	*ft_add_spaces(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		single_q;
	int		double_q;

	i = -1;
	j = 0;
	single_q = 0;
	double_q = 0;
	new_str = malloc(ft_strlen(str) * 3 + 2);
	while (str[++i])
	{
		if (str[i] == '\'' && double_q == 0)
			single_q = !single_q;
		else if (str[i] == '\"' && single_q == 0)
			double_q = !double_q;
		if (!single_q && !double_q)
			add_spaces_helper(&str, &i, &j, &new_str);
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
