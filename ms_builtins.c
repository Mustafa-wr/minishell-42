/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/24 01:45:54 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_pipe *p, int x, int y)
{
	y += 1;
	if (!p->args[x][y] || !p->args[x][y][0])
		printf("\n");
	else if (p->args[x][y][0] != '-' && p->args[x][y][1] != 'n' && !p->args[x][y - 1][4])
	{
		while (p->args[x][y])
		{
			printf("%s ", p->args[x][y]);
			y++;
		}
		printf("\n");
	}
	else if (p->args[x][y][0] == '-' && p->args[x][y][1] == 'n')
	{
		y += 1;
		if (!p->args[x][y])
			return ;
		while (p->args[x][y + 1])
		{
			printf("%s ", p->args[x][y]);
			y++;
		}
		printf("%s", p->args[x][y]);
	}
	else
		printf("%s: command not found\n", p->args[x][y - 1]);
}

void	ft_pwd(t_pipe *p)
{
	int		i;

	i = fork();
	(void)p;
	if (i == 0)
	{
		if (execve("/bin/pwd", p->args[0], 0) < 0)
		{
			perror("not found");
			return ;
		}
	}
	waitpid(i, NULL, 0);
	return ;
}
