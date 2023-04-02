/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:36:08 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/02 23:36:55 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(t_pipe *p, char **envp)
{
	int		i;

	i = 0;
	p->m_env = NULL;
	if (!envp[0])
	{
		write(2, "don't play with me(env -i)\n", 27);
		exit(1);
	}
	while (envp[i])
	{
		ft_lstadd_back(&p->m_env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	p->env_count = i;
	// printf("i = %d\n", i);
}

// void	ms_redirection(t_pipe *p)
// {
// 	int		i;
// 	int		k;
// 	int		pid;
// 	char	**str;
// 	char	*cmd;

// 	i = cmd_index(p);
// 	cmd = check_command_existence(p->args[0][i], p->m_path);
// 	printf("args = %s\n", p->args[0][i]);
// 	str = ft_split(p->args[0][i], ' ');
// 	// printf("cmd = %s\n", cmd);
// 	// printf("str = %s", str[1]);
// 	// exit(0);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		k = check_and_create(p, i);
// 		k = open(p->args[0][check_and_create(p, i)], O_WRONLY, 0777);
// 		dup2(k, STDOUT_FILENO);
// 		if (execve(cmd, str, p->m_env) < 0)
// 		{
// 			printf("command not found :%s\n", p->args[0][0]);
// 			return ;
// 		}
// 	}
// 	wait(NULL);
// }

// int	cmd_index(t_pipe *p)
// {
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (p->args[i])
// 	{
// 		j = 0;
// 		while (p->args[i][j])
// 		{
// 			k = 0;
// 			while (p->args[i][j][k])
// 			{
// 				if (p->args[i][j][k] == '>')
// 					return (i);				
// 				k++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	// printf("j = %d", j);
// 	return (0);
// }

// int	check_and_create(t_pipe *p, int i)
// {
// 	int		fd;
// 	int		x;

// 	// i = 0;
// 	x = 0;
// 	i += 1;
// 	// printf("%s\n", p->args[x][i]);
// 	while (p->args[x][i])
// 	{
// 		if (p->args[x][i][0] != '>')
// 			fd = open(p->args[x][i], O_RDWR | O_CREAT, 0777);
// 		i++;
// 	}
// 	i -= 1;
// 	// printf("%s\n", p->args[x][i]);
// 	return (i);
// }

void	fill_export(t_pipe *c)
{
	int		i;
	t_list	*tmp;
	int		index;

	i = 0;
	c->m_export = NULL;
	tmp = c->m_env;
	index = c->env_count;
	fill_tmp_env(c);
	while (tmp->next)
	{
		index = found_first(c->tmp_env, index, c);
		ft_lstadd_front(&c->m_export,
			ft_lstnew(ft_strdup(env_index(index, c->m_env))));
		c->tmp_env[index][0] = '0';
		tmp = tmp->next;
		if (!tmp)
			break ;
		i++;
	}
	last_sorting(c);
}

void	update_env(t_pipe *c)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = c->m_env;
	free_strings(c->tmp_env);
	c->tmp_env = malloc((c->env_count + 1) * sizeof(char *));
	while (tmp)
	{
		c->tmp_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	c->tmp_env[i] = NULL;
}
