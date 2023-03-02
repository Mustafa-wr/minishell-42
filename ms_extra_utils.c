/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:40:34 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/02 21:51:37 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strncmp_orginal(const char *s1, const char *s2, unsigned int n)
{
	size_t			i;
	unsigned char	*ns1;
	unsigned char	*ns2;

	ns1 = (unsigned char *)s1;
	ns2 = (unsigned char *)s2;
	i = 0;
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

int	found_first(char **m_env, int k, t_pipe *p)
{
	int		i;
	int		c;
	int		f;
	int		j;

	i = 0;
	f = 0;
	c = 0;
	j = 0;
	(void)k;
	k = p->env_count;
	while (m_env[i])
	{
		c = 0;
		f = i + 1;
		k = p->env_count;
		if (m_env[i + 1] != NULL && m_env[i] != NULL)
		{
			while ((int)m_env[i][j] > (int)m_env[f][j])
			{
				c++;
				f++;
				if (m_env[f] == NULL)
					break ;
				k--;
			}
			if (!m_env[f + 1])
				return (i);
		}
		i++;
	}
	return (0);
}

void	fill_export_list(t_pipe *p)
{
	int		i;

	i = 0;
	p->m_export = NULL;
	while (p->m_env[i])
	{
		ft_lstadd_back(&p->m_export, ft_lstnew(p->m_env[i]));
		i++;
	}
	// ft_lstadd_back(&p->m_export, NULL);
}

void	fill_tmp_env(t_pipe *p)
{
	int		i;

	i = 0;
	p->tmp_env = malloc((p->env_count + 1) * sizeof(char *));
	while (p->m_env[i])
	{
		p->tmp_env[i] = ft_strdup(p->m_env[i]);
		i++;
	}
	p->tmp_env[i] = NULL;
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
