/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:19:26 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/28 17:38:19 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_strings(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
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

// void replace_spaces_tabs(char *str)
// {
// 	int i = 0;
// 	int j = 0;
// 	int space_found = 0;

// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == ' ')
// 		{
// 			if (!space_found)
// 			{
// 				str[j++] = ' ';
// 				space_found = 1;
// 			}
// 		}
// 		else
// 		{
// 			str[j++] = str[i];
// 			space_found = 0;
// 		}
// 		i++;
// 	}
// 	str[j] = '\0';
// }

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
