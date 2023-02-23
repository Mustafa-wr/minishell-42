/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:40:39 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/24 01:56:41 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(t_pipe *p)
{
	int		j;
	int		x;

	x = 0;
	j = 0;
	// while (p->args[x])
	// {
	// 	while (p->args[x][j])
	// 	{
	// 		printf("%s\n", p->args[x][j]);
	// 		j++;
	// 	}
	// 	x++;
	// }
	// exit(0);
	while (p->args[x])
	{
		while (p->args[x][j])
		{
			if (ft_strncmp(p->args[x][j], "exit", 4) == 0)
				exit(0);
			else if ((p->args[x][j][0] == 'E' || p->args[x][j][0] == 'e') && (p->args[x][j][1] == 'C' || p->args[x][j][1] == 'c') && (p->args[x][j][2] == 'H' || p->args[x][j][2] == 'h') && (p->args[x][j][3] == 'o' || p->args[x][j][3] == 'O'))
				ft_echo(p, x, j);
			else if (ft_strncmp(p->args[x][j], "pwd", 3) == 0 && ft_strlen(p->args[x][j]) == 3)
				ft_pwd(p);
			else if (ft_strncmp(p->args[x][j], "env", 3) == 0 && ft_strlen(p->args[x][j]) == 3)
				ft_env(p);
			else if ()
			j++;
		}
		x++;
	}
}
