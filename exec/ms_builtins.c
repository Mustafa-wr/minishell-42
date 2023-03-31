/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/31 22:19:34 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmds *p, int x, int y, t_pipe *c)
{
	y += 1;
	c->fd1 = check_exec_rederict(p, c);
	if (c->fd1 == -1)
		return ;
	if (!p[x].cmd[y] || !p[x].cmd[y][0])
	{
		if (c->fd1 > 2)
		{
			write(c->fd1, "\n", 1);
			close(c->fd1);
		}
		else
			printf("\n");
	}
	else if (check_for_flag(p[x].cmd[y]) && !p[x].cmd[y - 1][4])
		echo_new_line(p, x, y, c);
	else if (check_for_flag(p[x].cmd[y]) == 0)
		echo_flag(p, x, y, c);
}

void	ft_pwd(t_cmds *p, t_pipe *c)
{
	int		i;

	(void)c;
	i = fork();
	if (i == 0)
	{
		if (p[0].red_len > 0)
		{
			c->fd1 = check_exec_rederict(p, c);
			dup2(c->fd1, STDOUT_FILENO);
			close(c->fd1);
		}
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
	t_list	*tmp;

	(void)p;
	(void)c;
	tmp = c->m_env;
	c->fd1 = check_exec_rederict(p, c);
	while (tmp)
	{
		if (p[0].red_len > 0)
		{
			ft_putstr_fd(tmp->content, c->fd1, 1);
		}
		else
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	if (c->fd1 > 2)
		close(c->fd1);
}

void	ft_cd(t_cmds *p, int x, int y, t_pipe *c)
{
	(void)c;
	y += 1;
	c->fd1 = check_exec_rederict(p, c);
	if (chdir(p[x].cmd[y]) < 0)
		printf("%s: No such file or directory\n", p[x].cmd[y]);
	if (c->fd1 > 2)
		close(c->fd1);
	return ;
}

void	ft_export(t_pipe *c, t_cmds *p, int i, int j)
{
	c->tmp = NULL;
	c->tmpp = c->m_export;
	c->fd1 = check_exec_rederict(p, c);
	j += 1;
	if (p[i].cmd[j])
	{
		insert_the_node(p, c);
	}
	else
	{
		while (c->tmpp)
		{
			if (p[0].red_len > 0)
			{
				ft_putstr_fd(c->tmpp->content, c->fd1, 1);
			}
			else
			{
				printf("declare -x %s\n", (char *)c->tmpp->content);
			}
			c->tmpp = c->tmpp->next;
		}
	}
	if (c->fd1 > 2)
		close(c->fd1);
}

void	ft_unset(t_cmds *p, int i, int j, t_pipe *c)
{
	c->fd1 = check_exec_rederict(p, c);
	if (!p[i].cmd[j + 1])
		return ;
	unset_cmp(p, c->m_env, i, j);
	unset_cmp(p, c->m_export, i, j);
	c->env_count -= 1;
	if (c->fd1 > 2)
		close(c->fd1);
}
