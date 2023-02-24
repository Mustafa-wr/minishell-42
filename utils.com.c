/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.com.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:36:08 by abdamoha          #+#    #+#             */
/*   Updated: 2023/02/24 02:45:32 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_pipe *p, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	p->m_env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		p->m_env[i] = ft_strdup(envp[i]);
		i++;
	}
	p->m_env[i] = NULL;
}
