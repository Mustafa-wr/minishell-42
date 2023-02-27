/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/27 14:51:37 by abdamoha         ###   ########.fr       */
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
	int		i;
	int		j;
	int		index;

	i = 0;
	p->m_export = NULL;
	index = p->env_count;
	j = p->env_count;
	(void)p;
	fill_tmp_env(p);
	while (p->m_env[i + 1])
	{
		// char *s = "abcdefg";
		// printf("len = %zu", ft_strlen(s + 2));
		// exit (0);
		index = found_first(p->tmp_env, index, p);
		// printf("i = %d\n", index);
		ft_lstadd_front(&p->m_export, ft_lstnew(p->m_env[index]));
		// printf("declare -x %s\n", p->m_env[index]);
		p->tmp_env[index][0] = '0';
		// p->env_count--;
		// index = found_first(p, p->env_count);
		// printf("i = %d\n", index);
		// printf("declare -x %s\n", p->m_env[index]);
		// p->m_env[index][0] = '0';
		// p->env_count--;
		// index = found_first(p, p->env_count);
		// printf("i = %d\n", index);
		// printf("declare -x %s\n", p->m_env[index]);
		// index = found_first(p, index);
		// printf("declare -x %s\n", p->m_env[index]);
		i++;
	}
	last_sorting(p);
	i = 0;
	while (i < 27)
	{
		printf("declare -x %s\n", p->m_export->content);
		p->m_export = p->m_export->next;
		i++;
	}
	free_strings(p->tmp_env);
	// printf("declare -x %s\n", p->m_export->content);
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
