/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:36:08 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 18:22:59 by abdamoha         ###   ########.fr       */
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
}

void	fill_export(t_pipe *c)
{
	c->m_export = NULL;
	fill_tmp_env(c);
	last_sorting(c);
	c->i = 0;
	while (c->tmp_env[c->i])
	{
		ft_lstadd_back(&c->m_export, ft_lstnew(ft_strdup(c->tmp_env[c->i])));
		c->i++;
	}
}

int	env_count(t_pipe *c)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = c->m_env;
	if (c->m_env && tmp)
	{
		while (tmp)
		{
			i++;
			if (tmp)
				tmp = tmp->next;
		}
	}
	return (i);
}

void	update_env(t_pipe *c)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = c->m_env;
	free_strings(c->tmp_env);
	c->env_count = env_count(c);
	c->tmp_env = malloc((c->env_count + 1) * sizeof(char *));
	while (tmp)
	{
		c->tmp_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	c->tmp_env[i] = NULL;
	i = 0;
}

void	error_in_exec(t_pipe *c, t_cmds *p)
{
	write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
	if (p[0].cmd[0])
		write(2, ": command not found\n", 21);
	g_exit_code = 127;
	free(c->cmd_exec);
	free_and_exit(c, p);
}
