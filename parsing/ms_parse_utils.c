/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:19:26 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/01 19:56:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	num_of_redirects(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			num++;
		}
		i++;
	}
	return (num);
}

void	free_3d(char ***av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			free(av[j][i]);
			i++;
		}
		free(av[j]);
		j++;
	}
	free(av);
}

static void increment(char *str, t_vars *vars)
{
	if (str[vars->i] == ' ')
	{
		if (!vars->space_found)
		{
			str[vars->j++] = ' ';
			vars->space_found = 1;
		}
	}
	else
	{
		str[vars->j++] = str[vars->i];
		vars->space_found = 0;
	}
}

void replace_spaces_tabs(char *str)
{
	t_vars vars;

	vars.i = 0;
	vars.j = 0;
	vars.space_found = 0;
	vars.quote_char = 0;
    while (str[vars.i] != '\0')
    {
        if (str[vars.i] == '"' || str[vars.i] == '\'')
        {
            if (vars.quote_char == 0)
                vars.quote_char = str[vars.i];
            else if (vars.quote_char == str[vars.i])
                vars.quote_char = 0;
			vars.space_found = 0;
            str[vars.j++] = str[vars.i];
        }
        else if (vars.quote_char == 0)
			increment(str, &vars);
        else
            str[vars.j++] = str[vars.i];
        vars.i++;
    }
    str[vars.j] = '\0';
}

void	remove_substr(char *s, unsigned int start, size_t len)
{
	// printf("start :%d\n", start);
	// printf("len :%zu\n", len);
	size_t	i;
	size_t	j;
    // /char *str;
	
	// str = malloc(sizeof(char) * (ft_strlen(s) - (len - start)) + 2);
    // if (!str || !s)
    //     return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (i < start || i >= len)
        {
            s[j] = s[i];
            j++;
        }
        i++;
    }
    s[j] = '\0';
	// free(s);
    // return (str);
}