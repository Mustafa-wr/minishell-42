/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:36:08 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/27 19:50:24 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_pipe *p, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	p->m_env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		p->m_env[i] = ft_strdup(envp[i]);
		// printf("i = %s\n", envp[i]);
		i++;
	}
	p->m_env[i] = NULL;
	p->env_count = i;
}

void	ms_redirection(t_pipe *p)
{
	int		i;
	int		k;
	int		pid;
	char	**str;
	char	*cmd;

	i = cmd_index(p);
	cmd = check_command_existence(p->args[0][i], p->m_path);
	printf("args = %s\n", p->args[0][i]);
	str = ft_split(p->args[0][i], ' ');
	// printf("cmd = %s\n", cmd);
	// printf("str = %s", str[1]);
	// exit(0);
	pid = fork();
	if (pid == 0)
	{
		k = check_and_create(p, i);
		k = open(p->args[0][check_and_create(p, i)], O_WRONLY, 0777);
		dup2(k, STDOUT_FILENO);
		if (execve(cmd, str, p->m_env) < 0)
		{
			printf("command not found :%s\n", p->args[0][0]);
			return ;
		}
	}
	wait(NULL);
}

int	cmd_index(t_pipe *p)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (p->args[i])
	{
		j = 0;
		while (p->args[i][j])
		{
			k = 0;
			while (p->args[i][j][k])
			{
				if (p->args[i][j][k] == '>')
					return (i);				
				k++;
			}
			j++;
		}
		i++;
	}
	// printf("j = %d", j);
	return (0);
}

int	check_and_create(t_pipe *p, int i)
{
	int		fd;
	int		x;

	// i = 0;
	x = 0;
	i += 1;
	// printf("%s\n", p->args[x][i]);
	while (p->args[x][i])
	{
		if (p->args[x][i][0] != '>')
			fd = open(p->args[x][i], O_RDWR | O_CREAT, 0777);
		i++;
	}
	i -= 1;
	// printf("%s\n", p->args[x][i]);
	return (i);
}

void	fill_export(t_pipe *p)
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
		index = found_first(p->tmp_env, index, p);
		ft_lstadd_front(&p->m_export, ft_lstnew(p->m_env[index]));
		p->tmp_env[index][0] = '0';
		i++;
	}
	last_sorting(p);
	// i = 0;
	// while (i < 27)
	// {
	// 	printf("declare -x %s\n", p->m_export->content);
	// 	p->m_export = p->m_export->next;
	// 	i++;
	// }
	free_strings(p->tmp_env);
}