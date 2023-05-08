/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_pipes_exec.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:23:49 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 12:53:40 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_p(t_cmds *p, int x, int pm, t_pipe *c)
{
	int	y;

	y = 1;
	g_exit_code = 0;
	(void)pm;
	if ((!p[x].cmd[y] || !p[x].cmd[y][0]))
		write (1, "\n", 1);
	else if (check_for_flag(p[x].cmd[y]) && !p[x].cmd[y - 1][4])
		echo_new_line(p, x, y, c);
	else if (check_for_flag(p[x].cmd[y]) == 0)
		echo_flag(p, x, y, c);
}

void	ft_pwd_p(t_cmds *p, t_pipe *c, int pm)
{
	char	*pwd;

	(void)p;
	(void)c;
	(void)pm;
	pwd = NULL;
	pwd = getcwd(NULL, 1024);
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		g_exit_code = 1;
	free(pwd);
	g_exit_code = 0;
}

void	ft_env_p(t_cmds *p, t_pipe *c, int pm)
{
	t_list	*tmp;

	(void)p;
	(void)pm;
	tmp = c->m_env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	if (c->fd1 > 2)
		close(c->fd1);
	g_exit_code = 0;
}

void	ft_cd_p(t_cmds *p, int x, int pm, t_pipe *c)
{
	int	y;

	(void)pm;
	y = 1;
	update_pwd(c, getcwd(NULL, 1024), "OLDPWD", 1);
	update_export(c, getcwd(NULL, 1024), "OLDPWD", 1);
	if (chdir(p[x].cmd[y]) < 0)
	{
		printf("%s: No such file or directory\n", p[x].cmd[y]);
		g_exit_code = 1;
	}
	else
		g_exit_code = 0;
	update_pwd(c, getcwd(NULL, 1024), "PWD", 0);
	update_export(c, getcwd(NULL, 1024), "PWD", 0);
}

void	ft_export_p(t_pipe *c, t_cmds *p, int i, int fd)
{
	(void)fd;
	c->tmp = NULL;
	c->tmpp = c->m_export;
	c->j = 1;
	if (p[i].cmd[c->j])
		insert_the_node(p, c);
	else
	{
		while (c->tmpp)
		{
			printf("declare -x %s\n", (char *)c->tmpp->content);
			c->tmpp = c->tmpp->next;
		}
		g_exit_code = 0;
	}
}
