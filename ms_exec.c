/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:40:39 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/26 17:44:35 by abdamoha         ###   ########.fr       */
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
	check_builtin(p);
	check_other(p);
}

void	check_builtin(t_pipe *p)
{
	int		j;
	int		x;

	x = 0;
	j = 0;
	while (p->args[x])
	{
		while (p->args[x][j])
		{
			if (ft_strncmp(p->args[x][j], "exit", 4) == 0)
				exit(0);
			else if (ft_strncmp(p->args[x][j], "cd", 2) == 0)
				ft_cd(p);
			else if (ft_strncmp(p->args[x][j], "export", 6) == 0)
				ft_export(p);
			else if (ft_strncmp(p->args[x][j], "unset", 5) == 0)
				ft_unset(p, x, j);
			else
			{
				ft_tolower(p->args[x][j]);
				if (ft_strncmp(p->args[x][j], "echo", 4) == 0)
					ft_echo(p, x, j);
				else if (ft_strncmp(p->args[x][j], "pwd", 3) == 0)
					ft_pwd(p);
				else if (ft_strncmp(p->args[x][j], "env", 3) == 0)
					ft_env(p);
			}
			j++;
		}
		x++;
	}
}

void	check_other(t_pipe *p)
{
	int		flag;
	int		len;

	p->i = 0;
	p->j = 0;
	p->m_path = check_env_for_path(p->m_env);
	// printf("p->p = %s", check_env_for_path(p->m_env));
	// exit(0);
	flag = check_for_redirction(p);
	len = count_cmds(p->args);
	if (flag == 0)
		normal_exec(p);
}

int	check_for_redirction(t_pipe *p)
{
	int		c;

	c = 0;
	p->i = 0;
	p->j = 0;
	while (p->args[p->i])
	{
		p->j = 0;
		while (p->args[p->i][p->j])
		{
			c = 0;
			while (p->args[p->i][p->j][c])
			{
				if (p->args[p->i][p->j][c] == '>'
				|| p->args[p->i][p->j][c] == '<')
					return (1);
				c++;
			}
			p->j++;
		}
		p->i++;
	}
	return (0);
}

void	normal_exec(t_pipe *p)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = check_command_existence(p->args[0][0], p->m_path);
	// printf("cmd = %s", cmd);
	// exit(0);
	i = fork();
	if (i == 0)
	{
		if (execve(cmd, p->args[0], p->m_env) < 0)
		{
			printf("command not found :%s\n", p->args[0][0]);
			return ;
		}
	}
	wait(NULL);

}
