/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:40:34 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 18:24:17 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strncmp_orginal(const char *s1, const char *s2, unsigned int n)
{
	size_t			i;
	unsigned char	*ns1;
	unsigned char	*ns2;

	i = 0;
	if (!s1 || !s2)
		return (1);
	ns1 = (unsigned char *)s1;
	ns2 = (unsigned char *)s2;
	while (i < n && ns1[i] != '\0' && ns2[i] != '\0')
	{
		if (ns1[i] != ns2[i])
			return (ns1[i] - ns2[i]);
		i++;
	}
	if (i != n)
		return (ns1[i] - ns2[i]);
	return (0);
}

int	my_fun(char **m_env, t_vars *v, int *k)
{
	if (m_env[v->i + 1] != NULL && m_env[v->i] != NULL)
	{
		while ((int)m_env[v->i][v->j] > (int)m_env[v->f][v->j])
		{
			v->c++;
			v->f++;
			if (m_env[v->f] == NULL)
				break ;
			(*k)--;
		}
		if (m_env[v->f] != NULL)
		{
			if (!m_env[v->f + 1])
				return (v->i);
		}
		else
			return (v->i);
	}
	return (-42);
}

int	found_first(char **m_env, int k, t_pipe *p)
{
	t_vars	v;

	v.i = 0;
	v.f = 0;
	v.c = 0;
	v.j = 0;
	k = p->env_count;
	while (m_env[v.i])
	{
		v.c = 0;
		v.f = v.i + 1;
		k = p->env_count;
		if (my_fun(m_env, &v, &k) != -42)
			return (v.i);
		v.i++;
	}
	return (0);
}

// int	found_first(char **m_env, int k, t_pipe *p)
// {
// 	int		i;
// 	int		c;
// 	int		f;
// 	int		j;

// 	i = 0;
// 	f = 0;
// 	c = 0;
// 	j = 0;
// 	k = p->env_count;
// 	while (m_env[i])
// 	{
// 		c = 0;
// 		f = i + 1;
// 		k = p->env_count;
// 		if (m_env[i + 1] != NULL && m_env[i] != NULL)
// 		{
// 			while ((int)m_env[i][j] > (int)m_env[f][j])
// 			{
// 				c++;
// 				f++;
// 				if (m_env[f] == NULL)
// 					break ;
// 				k--;
// 			}
// 			if (m_env[f] != NULL)
// 			{
// 				if (!m_env[f + 1])
// 					return (i);
// 			}
// 			else
// 				return (i);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	fill_export_list(t_pipe *p)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = p->m_env;
	p->m_export = NULL;
	while (tmp)
	{
		ft_lstadd_back(&p->m_export, ft_lstnew(tmp->content));
		tmp = tmp->next;
		i++;
	}
}

void	fill_tmp_env(t_pipe *c)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = c->m_env;
	c->tmp_env = malloc((c->env_count + 1) * sizeof(char *));
	while (tmp)
	{
		c->tmp_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	c->tmp_env[i] = NULL;
}

int	count_cmds(char ***str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
