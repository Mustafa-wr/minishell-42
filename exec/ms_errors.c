/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:48:56 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/10 23:52:14 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_error(t_cmds *p, t_pipe *c)
{
	perror("execve : is directory");
	g_exit_code = 126;
	free(c->cmd_exec);
	free_and_exit(c, p);
}

void	exit_status(t_pipe *c)
{
	if (WIFEXITED(c->status))
		g_exit_code = WEXITSTATUS(c->status);
	else if (WIFSIGNALED(c->status))
		g_exit_code = WTERMSIG(c->status) + 128;
	free(c->cmd_exec);
	c->cmd_exec = NULL;
	c->ch = 0;
}

int	check_if_file(t_cmds *p)
{
	struct stat	fs;

	if (stat(p[0].cmd[0], &fs) != 0)
	{
		perror("stat");
		g_exit_code = 126;
		return (1);
	}
	return (0);
}

int	check_dir(t_cmds *p)
{
	struct stat	fs;

	if (stat(p[0].cmd[0], &fs) != 0)
	{
		perror("stat");
		g_exit_code = 127;
		return (1);
	}
	return (0);
}

void	export_add(t_pipe *c, int i, int j, t_cmds *p)
{
	c->tmp2 = ft_lstnew(ft_strdup(p[0].cmd[j]));
	c->tmp2->next = c->tmpp;
	if (i != 0)
		c->tmp3->next = c->tmp2;
	c->env_count += 1;
	ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
	if (i == 0)
		c->m_export = c->tmp2;
}
