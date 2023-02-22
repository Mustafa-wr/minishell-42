/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:19:26 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/22 17:36:28 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
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
