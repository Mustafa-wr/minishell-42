/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/19 00:24:28 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmds *p, int x, int y, t_pipe *c)
{
	y += 1;
	// (void)c;
	// printf("e = %s\n", p[x].outs[1].file_name);
	// exit(0);
	// c->fd1 = 0;
	// printf("c-> = %d", c->fd1);
	// exit(0);
	// printf("fd1 = %d\n", c->fd1);
	if (!p[x].cmd[y] || !p[x].cmd[y][0])
	{
		printf("heeeereeeeeee1\n");
		printf("\n");
	}
	else if (check_for_flag(p[x].cmd[y]) && !p[x].cmd[y - 1][4])
	{
		// printf("heeeereeeeeee2\n");
		while (p[x].cmd[y])
		{
			if (p[x].red_len == 0)
				printf("%s ", p[x].cmd[y]);
			else
			{
				c->fd1 = check_exec_rederict(p, c);
				// printf("c = %d", c->fd1);
				write_in_fd(p, x, y, c);
				write(c->fd1, "\n", 1);
				close(c->fd1);
				return ;
				// printf("kll");
				// exit(0);
			}
			y++;
		}
		// close(c->fd1);
		// printf("\n");
		return ;
	}
	else if (check_for_flag(p[x].cmd[y]) == 0)
	{
		printf("heeeereeeeeee");
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
	close(c->fd1);
	free_all(c, p);
}

void	ft_pwd(t_cmds *p, t_pipe *c)
{
	int		i;

	(void)c;
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
	free_all(c, p);
	return ;
}

void	ft_env(t_cmds *p, t_pipe *c)
{
	// int		i;
	t_list	*tmp;

	// i = 0;
	(void)p;
	(void)c;
	tmp = c->m_env;
	// printf("c = %d\n", c->env_count);
	// exit(0);
	while (tmp)
	{
		// if (!tmp->content)
		// 	i++;
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
		// i++;
	}
	free_all(c, p);
}

void	ft_cd(t_cmds *p, int x, int y, t_pipe *c)
{
	(void)c;
	y += 1;
	if (chdir(p[x].cmd[y]) < 0)
		printf("ERROR\n");
	free_all(c, p);
	return ;
}

void	ft_export(t_pipe *c, t_cmds *p, int i, int j)
{
	int	k = 0;
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
			if (tmp->content != NULL)
				printf("declare -x %s\n", (char *)tmp->content);
			tmp = tmp->next;
			k++;
		}
		printf("i = %d\n", k);
	}
	free_all(c, p);
}

void	ft_unset(t_cmds *p, int i, int j, t_pipe *c)
{
	if (!p[i].cmd[j + 1])
		return ;
	unset_cmp(p, c->m_env, i, j);
	unset_cmp(p, c->m_export, i, j);
	c->env_count -= 1;
}
