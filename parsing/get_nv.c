/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:35:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 17:42:25 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(const char *name, t_pipe *pipe)
{
	char	*value;
	size_t	name_len;
	t_list	*env;
	char	*key;

	value = NULL;
	name_len = ft_strlen(name);
	env = pipe->m_env;
	while (env != NULL)
	{
		key = (char *) env->content;
		if (strncmp(key, name, name_len) == 0 && key[name_len] == '=')
		{
			value = key + name_len + 1;
			break ;
		}
		env = env->next;
	}
	return (value);
}
