/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:35:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/11 20:22:26 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	enviro(t_pipe *s, char **envp)
{
	int i = 0;

	while (envp[i])
		i++;
	s->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		s->env[i] = ft_strdup(envp[i]);
		i++;
	}
	s->env[i] = NULL;
}

char	*my_getenv(const char *name, t_pipe *pipe)
{
	char	*value;
	size_t	name_len;
	char	**env;
	int		i;

	value = NULL;
	name_len = ft_strlen(name);
	env = pipe->env;
	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], name, name_len) == 0 && (env[i])[name_len] == '=')
		{
			value = env[i] + name_len + 1;
			break ;
		}
		i++;
	}
	return (value);
}
