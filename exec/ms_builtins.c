/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by abdamoha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 18:05:11 by mradwan          ###   ########.fr       */
=======
/*   Updated: 2023/03/14 00:54:19 by abdamoha         ###   ########.fr       */
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmds *p, int x, int pm, t_pipe *c)
{
	int	y;

	y = 1;
	(void)pm;
	if (p->red_len > 0 && pm != 1)
		if (check_exec_redirect(p, c, 0, x) < 0)
			return ;
	if (!p[x].cmd[y] || !p[x].cmd[y][0])
		printf("\n");
	else if (check_for_flag(p[x].cmd[y]) && !p[x].cmd[y - 1][4])
		echo_new_line(p, x, y, c);
	else if (check_for_flag(p[x].cmd[y]) == 0)
		echo_flag(p, x, y, c);
}

void	ft_pwd(t_cmds *p, t_pipe *c, int pm)
{
	char	*pwd;

	(void)p;
	pwd = NULL;
	if (p->red_len > 0 && pm != 1 && c->cr != 1)
		check_exec_redirect(p, c, 0, 0);
	pwd = getcwd(NULL, 1024);
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		g_exit_code = 1;
	free(pwd);
	g_exit_code = 0;
}

void	ft_env(t_cmds *p, t_pipe *c, int pm)
{
<<<<<<< HEAD
	t_list	*tmp;

	(void)p;
	(void)c;
	tmp = c->m_env;
	if (p->red_len > 0 && pm != 1 && c->cr != 1)
		check_exec_redirect(p, c, 0, 0);
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
=======
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
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
	}
	g_exit_code = 0;
}

void	ft_cd(t_cmds *p, int x, int pm, t_pipe *c)
{
	int	y;

	y = 1;
	if (p->red_len > 0 && pm != 1 && c->cr != 1)
		check_exec_redirect(p, c, 0, 0);
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

void	ft_export(t_pipe *c, t_cmds *p, int i, int fd)
{
<<<<<<< HEAD
	(void)fd;
	c->tmp = NULL;
	c->tmpp = c->m_export;
	if (p->red_len > 0 && c->cr != 1)
		check_exec_redirect(p, c, 0, 0);
	c->j = 1;
	if (p[i].cmd[c->j])
=======
	int	k = 0;
	t_list	*tmp;

	tmp = c->m_export;
	j += 1;
	if (p[i].cmd[j])
	{
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
		insert_the_node(p, c);
	else
	{
		while (c->tmpp)
		{
<<<<<<< HEAD
			printf("declare -x %s\n", (char *)c->tmpp->content);
			c->tmpp = c->tmpp->next;
		}
		g_exit_code = 0;
=======
			if (tmp->content != NULL)
				printf("declare -x %s\n", (char *)tmp->content);
			tmp = tmp->next;
			k++;
		}
		printf("i = %d\n", k);
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
	}
}

