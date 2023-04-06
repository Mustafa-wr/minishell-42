/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:12:58 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 07:28:24 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_pipe *c, char *str, char *p, int k)
{
	c->tmpp = c->m_env;
	while(c->tmpp)
	{
		if (strncmp_orginal(p, c->tmpp->content, len_till_equal(c->tmpp->content)) == 0)
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
	while(c->tmpp)
	{
		if (strncmp_orginal(p, c->tmpp->content, len_till_equal(c->tmpp->content)) == 0)
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