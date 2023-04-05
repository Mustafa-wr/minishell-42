/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:59 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/05 00:40:07 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list **lst)
{
	t_list	*tmp;

	while ((*lst)->next)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
	free((*lst)->content);
	free(*lst);
}

void	free_and_exit(t_pipe *c, t_cmds *p)
{
	(void)p;
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);
	free_all(c, p);
	// printf("g = %d\n", g_exit_code);
	// closing_fds(c);
	close(c->fdin);
	close(c->fdout);
	exit(g_exit_code);
}

void	free_and_exit_2(t_pipe *c, t_cmds *p)
{
	(void)p;
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);

	close(c->fdout);
	close(c->fdin);
}

static int	check_exit(t_cmds *p, int k)
{
	int	i;

	i = 0;
	if (p[0].cmd[1])
	{
		if (k == 0)
		{
			while (p[0].cmd[1][i])
			{
				if (!ft_isalpha(p[0].cmd[1][i]))
					return (1);
				i++;
			}
		}
		else
		{
			if (ft_atoi(p[0].cmd[1]) > INT_MAX || ft_atoi(p[0].cmd[1]) < INT_MIN)
				return (1);
		}
	}
	return (0);
}
void	ft_exit(t_pipe *c, t_cmds *p)
{
	if (check_exit(p, 0) == 0 || check_exit(p, 1) == 1)
	{
		write(2, "numeric argument required\n", 26);
		g_exit_code = 255;
	}
	else if (p[0].cmd[1])
		g_exit_code = ft_atoi(p[0].cmd[1]);
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);
	close(c->fdin);
	close(c->fdout);
	free_all(c, p);
	exit(g_exit_code);
}
