/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/02 20:18:23 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmds *p, int x, int y)
{
	y += 1;
	if (!p[x].cmd[y] || !p[x].cmd[y][0])
		printf("\n");
	else if (p[x].cmd[y][0] != '-' && p[x].cmd[y][1] != 'n' && !p[x].cmd[y - 1][4])
	{
		while (p[x].cmd[y])
		{
			printf("%s ", p[x].cmd[y]);
			y++;
		}
		printf("\n");
	}
	else if (p[x].cmd[y][0] == '-' && p[x].cmd[y][1] == 'n')
	{
		y += 1;
		if (!p[x].cmd[y])
			return ;
		while (p[x].cmd[y + 1])
		{
			printf("%s ", p[x].cmd[y]);
			y++;
		}
		printf("%s", p[x].cmd[y]);
	}
	else
		printf("%s: command not found\n", p[x].cmd[y - 1]);
}

void	ft_pwd(t_cmds *p)
{
	int		i;

	i = fork();
	if (i == 0)
	{
		if (execve("/bin/pwd", p[0].cmd, 0) < 0)
		{
			perror("not found");
			return ;
		}
	}
	waitpid(i, NULL, 0);
	return ;
}

void	ft_env(t_cmds *p, t_pipe *c)
{
	int		i;

	i = 0;
	(void)p;
	while (i < c->env_count)
	{
		if (c->m_env[i] == NULL)
			i++;
		printf("%s\n", c->m_env[i]);
		i++;
	}
	// printf("HOME :%s\n", getenv("HOME"));
	// printf("PATH :%s\n", getenv("PATH"));
	// printf("ROOT :%s\n", getenv("ROOT"));
}

// void	ft_cd(t_pipe *p)
// {
// 	(void)p;
// }

void	ft_export(t_pipe *c, t_cmds *p, int i, int j)
{
	t_list	*tmp;

	tmp = c->m_export;
	j += 1;
	if (p[i].cmd[j])
	{
		insert_the_node(p, c);
	}
	else
	{
		while (tmp)
		{
			printf("declare -x %s\n", tmp->content);
			// sleep(1);
			tmp = tmp->next;
		}
	}
}

void	ft_unset(t_cmds *p, int i, int j, t_pipe *c)
{
	int		counter;

	counter = 0;
	if (!p[i].cmd[j + 1])
		return ;
	while (c->m_env[counter])
	{
		if (strncmp_orginal(c->m_env[counter], p[i].cmd[j + 1],
				len_till_equal(p[i].cmd[j + 1])) == 0)
		{
			c->m_env[counter] = NULL;
			c->env_count -= 1;
			return ;
		}
		counter++;
	}
}
