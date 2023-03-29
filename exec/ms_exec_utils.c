/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:20:54 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/28 17:40:39 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**check_env_for_path(t_list *env)
// {
// 	int		i;
// 	char	*s;
// 	t_list	*tmp;

// 	i = 0;
// 	s = NULL;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (strncmp_orginal("PATH=", tmp->content, 5) == 0)
// 		{
// 			s = tmp->content + 5;
// 			return (ft_split(s, ':'));
// 		}
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return (NULL);
// }

char	*check_command_existence(char *av, char **path)
{
	int		i;
	char	*str;
	char	*join;
	int		j;

	j = 0;
	i = ft_strlen(av);
	if (i == 0)
		return (NULL);
	if (ft_strchr(av, '/') != NULL)
	{
		return (backslash_case(av, i));
	}
	str = malloc(i + 2);
	str[0] = '/';
	i = 1;
	while (av[j] != '\0' && av[i - 1] != ' ')
	{
		str[i] = av[j];
		j++;
		i++;
	}
	str[i] = '\0';
	join = check_with_access(path, str);
	return (join);
}

char	*check_with_access(char **path, char *str)
{
	int		i;
	char	*join;

	i = 0;
	join = NULL;
	if (path)
	{
		while (path[i] != NULL)
		{
			join = ft_strjoin(path[i], str);
			if (access(join, X_OK) != -1)
			{
				return (free(str), join);
			}
			i++;
			free(join);
			join = NULL;
		}
	}
	return (free(join), free(str), NULL);
}

char	*backslash_case(char *av, int i)
{
	int		j;
	char	*join;

	j = 0;
	join = malloc(i + 1);
	while (av[j] != '\0')
	{
		join[j] = av[j];
		j++;
	}
	join[j] = '\0';
	return (join);
}

void	last_sorting(t_pipe *p)
{
	t_list	*tmp;
	char	*str;
	// char	*s1;
	// char	*s2;

	tmp = p->m_export;
	while (tmp)
	{
		if (tmp->next)
		{
			if (strncmp_orginal(tmp->content, tmp->next->content, len_till_equal(tmp->content)) > 0)
			{
				str = tmp->content;
				tmp->content = tmp->next->content;
				tmp->next->content = str;
			}
		}
		tmp = tmp->next;
	}
}
