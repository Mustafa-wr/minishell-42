/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:12:58 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 18:12:37 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_pipe *c, char *str, char *p, int k)
{
	c->tmpp = c->m_env;
	while (c->tmpp)
	{
		if (strncmp_orginal(p, c->tmpp->content,
				len_till_equal(c->tmpp->content)) == 0)
		{
			free(c->tmpp->content);
			if (k == 0)
				c->tmpp->content = ft_strjoin("PWD=", str);
			else
				c->tmpp->content = ft_strjoin("OLDPWD=", str);
			break ;
		}
		c->tmpp = c->tmpp->next;
	}
	free(str);
}

void	update_export(t_pipe *c, char *str, char *p, int k)
{
	c->tmpp = c->m_export;
	while (c->tmpp)
	{
		if (strncmp_orginal(p, c->tmpp->content,
				len_till_equal(c->tmpp->content)) == 0)
		{
			free(c->tmpp->content);
			if (k == 0)
				c->tmpp->content = ft_strjoin("PWD=", str);
			else
				c->tmpp->content = ft_strjoin("OLDPWD=", str);
			break ;
		}
		c->tmpp = c->tmpp->next;
	}
	free(str);
}

int	ft_strcmp_heredoc(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	init_export(t_vars *v, t_pipe *p)
{
	v->i = 0;
	v->f = 0;
	v->c = 0;
	v->j = 0;
	v->k = env_count(p);
}

void	wait_pipes(t_vars *v, t_pipe *c, t_cmds *p)
{
	v->h = 0;
	while (v->h < p->cmd_len)
	{
		wait(&c->status);
		if (v->h == p->cmd_len - 1)
			exit_code_pipes(c, v);
		v->h++;
	}
	c->cr = 0;
	c->p_f1 = 0;
	c->p_f2 = 0;
}
