/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:40:34 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/26 19:21:36 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strncmp_orginal(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (ss1[i] != '\0' && ss2[i] != '\0' && i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i != n)
		return (ss1[i] - ss2[i]);
	return (0);
}

int	found_first(char **m_env, int k, t_pipe *p)
{
	int		i;
	int		n1;
	int		c;
	int		f;
	int		n2;
	int		j;

	i = 0;
	f = 0;
	c = 0;
	j = 0;
	n1 = 0;
	n2 = 0;
	// (void)p;
	(void)k;
	k = p->env_count;
	while (m_env[i])
	{
		c = 0;
		f = i + 1;
		k = p->env_count;
		// n1 = m_env[i][j];
		// // if (m_env[f + 1])
		// n2 = m_env[i + 1][j];
		// printf("n1 = %d\n", n1);
		// printf("n2 = %d\n", n2);
		if (m_env[i + 1] != NULL && m_env[i] != NULL)
		{
			while ((int)m_env[i][j] > (int)m_env[f][j])
			{
				// printf("i = %d && c = %c ", i, m_env[i][j]);
				// printf("f = %d && c = %c\n", f, m_env[f][j]);
				if ((int)m_env[i][j] == (int)m_env[f][j])
				{
						// printf("iff = %d\n", strncmp_orginal(m_env[i], m_env[f], ft_strlen(m_env[i])));
					if (strncmp_orginal(m_env[i], m_env[f + 1], ft_strlen(m_env[i])) > 0)
					{
						return (i);
					}
				}
				c++;
				f++;
				// j--;
				if (m_env[f] == NULL)
					break ;
				k--;
			}
			// printf("k = %d", k);
			// printf("en = %d", env_count);
			// printf("c = %d", c);
			// printf("n = %s\n", m_env[f]);
			if (!m_env[f + 1])
			{
				// printf("it = %d", i);
				return (i);
			}
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
