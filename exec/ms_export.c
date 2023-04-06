/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:04:59 by abdamoha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 18:18:24 by mradwan          ###   ########.fr       */
=======
/*   Updated: 2023/03/14 00:27:51 by abdamoha         ###   ########.fr       */
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_equal(t_cmds *p, int i, int j)
{
	int		k;

	k = 0;
	while (p[i].cmd[j][k])
	{
		if (p[i].cmd[j][k] == '=')
			return (1);
		k++;
	}
	return (0);
}

void	ch_t_val(t_cmds *p, int i, int j, t_vars *v)
{
	while (v->tmp)
	{
		if (strncmp_orginal(v->tmp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
<<<<<<< HEAD
			v->tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			v->tmp3->next = v->tmp->next;
			if (v->tmp2->content != v->tmp->content)
				v->tmp2->next = v->tmp3;
			break ;
		}
		v->tmp2 = v->tmp;
		v->tmp = v->tmp->next;
		v->k++;
	}
}

void	changing_the_value(t_cmds *p, int i, int j, t_pipe *c)
{
	t_vars	v;

	v.k = 0;
	v.tmp = c->m_export;
	v.tmp2 = v.tmp;
	v.tmp3 = NULL;
	ch_t_val(p, i, j, &v);
	if (v.tmp2->content != v.tmp->content)
		v.tmp2->next = v.tmp3;
	if (v.k == 0)
	{
		c->m_export = v.tmp3;
		free(v.tmp->content);
		free(v.tmp);
	}
=======
			tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
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
	tmp2->next = tmp3;
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
}

// void	changing_the_value(t_cmds *p, int i, int j, t_pipe *c)
// {
// 	int		k;
// 	t_list	*tmp;
// 	t_list	*tmp2;
// 	t_list	*tmp3;

// 	k = 0;
// 	tmp = c->m_export;
// 	tmp2 = tmp;
// 	tmp3 = NULL;
// 	while (tmp)
// 	{
// 		if (strncmp_orginal(tmp->content, p[i].cmd[j],
// 				len_till_equal(p[i].cmd[j])) == 0)
// 		{
// 			tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
// 			tmp3->next = tmp->next;
// 			if (tmp2->content != tmp->content)
// 				tmp2->next = tmp3;
// 			break ;
// 		}
// 		tmp2 = tmp;
// 		tmp = tmp->next;
// 		k++;
// 	}
// 	if (tmp2->content != tmp->content)
// 		tmp2->next = tmp3;
// 	free(tmp->content);
// 	free(tmp);
// 	if (k == 0)
// 		c->m_export = tmp3;
// }

char	*env_index(int index, t_list *env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = env;
	while (i < index && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp)
		return (tmp->content);
	else
		return (NULL);
}

void	ch_the_env(t_cmds *p, int i, int j, t_vars *v)
{
	while (v->tmp)
	{
		if (strncmp_orginal(v->tmp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
<<<<<<< HEAD
			v->tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			v->tmp3->next = v->tmp->next;
			if (v->tmp2->content != v->tmp->content)
				v->tmp2->next = v->tmp3;
			break ;
		}
		v->tmp2 = v->tmp;
		v->tmp = v->tmp->next;
		v->k++;
	}
}

void	changing_the_env_v(t_cmds *p, int i, int j, t_pipe *c)
{
	t_vars	v;

	v.k = 0;
	v.tmp = c->m_env;
	v.tmp2 = v.tmp;
	v.tmp3 = NULL;
	ch_the_env(p, i, j, &v);
	if (v.tmp2->content != v.tmp->content)
		v.tmp2->next = v.tmp3;
	if (v.k == 0)
	{
		c->m_export = v.tmp3;
		free(v.tmp->content);
		free(v.tmp);
	}
=======
			tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
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
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
}

// void	changing_the_env_v(t_cmds *p, int i, int j, t_pipe *c)
// {
// 	int		k;
// 	t_list	*tmp;
// 	t_list	*tmp2;
// 	t_list	*tmp3;

// 	k = 0;
// 	tmp = c->m_env;
// 	tmp2 = tmp;
// 	tmp3 = NULL;
// 	while (tmp)
// 	{
// 		if (strncmp_orginal(tmp->content, p[i].cmd[j],
// 				len_till_equal(p[i].cmd[j])) == 0)
// 		{
// 			tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
// 			tmp3->next = tmp->next;
// 			if (tmp2->content != tmp->content)
// 				tmp2->next = tmp3;
// 			break ;
// 		}
// 		tmp2 = tmp;
// 		tmp = tmp->next;
// 		k++;
// 	}
// 	if (tmp2->content != tmp->content)
// 		tmp2->next = tmp3;
// 	if (tmp)
// 	{
// 		free(tmp->content);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	if (k == 0)
// 		c->m_export = tmp3;
// }

void	unset_cmp(t_list *lst, char *str)
{
	t_list	*tmp3;
	t_list	*tmp2;
	t_list	*tmp;

	tmp = lst;
	tmp2 = tmp;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, str, len_till_equal(str)) == 0)
		{
			tmp3 = tmp->next;
<<<<<<< HEAD
			tmp2->next = tmp3;
			free(tmp->content);
			free(tmp);
=======
			free(tmp->content);
			free(tmp);
			tmp2->next = tmp3;
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
			return ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}
