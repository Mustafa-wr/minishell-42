/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:35:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/12 17:02:25 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(t_pipe *p, char **envp)
{
	int		i;

	i = 0;
	p->m_env = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&p->m_env, ft_lstnew(envp[i]));
		i++;
	}
	p->env_count = i;
}

// char	*my_getenv(const char *name, t_pipe *pipe)
// {
// 	char	*value;
// 	size_t	name_len;
// 	char	**env;
// 	int		i;

// 	value = NULL;
// 	name_len = ft_strlen(name);
// 	env = pipe->env;
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (strncmp(env[i], name, name_len) == 0 && (env[i])[name_len] == '=')
// 		{
// 			value = env[i] + name_len + 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (value);
// }

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

