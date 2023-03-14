/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:20:21 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/14 08:02:11 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_executable(t_pipe *c, t_cmds *p)
{
	int		i;

	i = 0;
	if (ft_strchr(p[i].cmd[0], '.') && ft_strchr(p[i].cmd[0], '/'))
	{
		if (ft_strncmp(p[i].cmd[0], "./minishell", 11) == 0)
		{
			change_shlv(p, c, c->m_env);
			change_shlv(p, c, c->m_export);
			return (1);
		}
	}
	return (0);
}

void	change_shlv(t_cmds *p, t_pipe *c, t_list *lst)
{
	int		k;
	char	*s;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;

	k = 0;
	s = NULL;
	tmp = lst;
	tmp2 = tmp;
	tmp3 = NULL;
	(void)p;
	(void)c;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, "SHLVL=",
				len_till_equal("SHLVL=")) == 0)
		{
			s = ft_itoa(increase_shlvl_value(tmp->content));
			tmp3 = ft_lstnew(ft_strjoin("SHLVL=", s));
			tmp3->next = tmp->next;
			tmp2->next = tmp3;
			free(tmp->content);
			free(tmp);
			break ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
		k++;
	}
	if (s)
		free(s);
}

int	increase_shlvl_value(char *str)
{
	int	i;

	i = len_till_equal(str) + 1;
	return (ft_atoi(str + i) + 1);
}
