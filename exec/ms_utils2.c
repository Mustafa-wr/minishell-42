/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:36:08 by abdamoha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 19:13:21 by mradwan          ###   ########.fr       */
=======
/*   Updated: 2023/03/14 07:05:29 by abdamoha         ###   ########.fr       */
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(t_pipe *p, char **envp)
{
	int		i;

	i = 0;
	p->m_env = NULL;
	if (!envp[0])
	{
		write(2, "don't play with me(env -i)\n", 27);
		exit(1);
	}
	while (envp[i])
	{
		ft_lstadd_back(&p->m_env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	p->env_count = i;
	printf("i = %d\n", i);
}

void	fill_export(t_pipe *c)
{
	int		i;
	t_list	*tmp;
	int		index;

	i = 0;
	c->m_export = NULL;
	tmp = c->m_env;
	index = c->env_count;
	fill_tmp_env(c);
	while (tmp->next)
	{
		index = found_first(c->tmp_env, index, c);
		ft_lstadd_front(&c->m_export,
			ft_lstnew(ft_strdup(env_index(index, c->m_env))));
		c->tmp_env[index][0] = '0';
		tmp = tmp->next;
		if (!tmp)
			break ;
		i++;
	}
	last_sorting(c);
}

<<<<<<< HEAD
static int	env_count(t_pipe *c)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = c->m_env;
	if (c->m_env && tmp)
	{
		while (tmp)
		{
			i++;
			if (tmp)
				tmp = tmp->next;
		}
	}
	return (i);
}

=======
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
void	update_env(t_pipe *c)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = c->m_env;
	free_strings(c->tmp_env);
<<<<<<< HEAD
	c->env_count = env_count(c);
=======
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
	c->tmp_env = malloc((c->env_count + 1) * sizeof(char *));
	while (tmp)
	{
		c->tmp_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	c->tmp_env[i] = NULL;
<<<<<<< HEAD
	i = 0;
=======
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
}
