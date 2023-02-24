/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/24 22:34:55 by abdamoha         ###   ########.fr       */
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

void	ft_env(t_pipe *p)
{
	int		i;

	i = 0;
	(void)p;
	while (i < p->env_count)
	{
		if (p->m_env[i] == NULL)
			i++;
		printf("%s\n", p->m_env[i]);
		i++;
	}
	// printf("HOME :%s\n", getenv("HOME"));
	// printf("PATH :%s\n", getenv("PATH"));
	// printf("ROOT :%s\n", getenv("ROOT"));
}

void	ft_cd(t_pipe *p)
{
	(void)p;
}

void	ft_export(t_pipe *p)
{
	(void)p;
	getenv("export");
}

void	ft_unset(t_pipe *p, int i, int j)
{
	int		counter;

	counter = 0;
	if (!p->args[i][j + 1])
		return ;
	// printf("p = %s\n", p->args[i][j + 1]);
	while (p->m_env[counter])
	{
		if (strncmp_orginal(p->m_env[counter], p->args[i][j + 1],
			ft_strlen(p->args[i][j + 1])) == 0)
		{
			p->m_env[counter] = NULL;
			p->env_count -= 1;
			return ;
		}
		// printf("env = %s\n", p->m_env[counter]);
		// printf("p = %s\n", p->args[i][j + 1]);
		counter++;
	}
	// printf("\n\n");
	// printf("c =  %d", counter);
	// i = 0;
	// while (i < p->env_count)
	// {
	// 	if (p->m_env[i] == NULL)
	// 		i++;
	// 	printf("%s\n", p->m_env[i]);
	// 	i++;
	// }
	// printf("unset: `%s': Not Valid identifier", p->args[i][j + 1]);
}
