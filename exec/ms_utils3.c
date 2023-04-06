/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:14:04 by abdamoha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 19:12:47 by mradwan          ###   ########.fr       */
=======
/*   Updated: 2023/03/14 00:39:16 by abdamoha         ###   ########.fr       */
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_ex(t_cmds *p, t_pipe *c, int *i, int j)
{
	c->tmp2 = ft_lstnew(ft_strdup(p[0].cmd[j]));
	c->tmp2->next = c->tmpp;
	if (i != 0)
		c->tmp3->next = c->tmp2;
	c->env_count += 1;
	ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
	if (i == 0)
		c->m_export = c->tmp2;
}

void	add_to_e2(t_cmds *p, t_pipe *c, int j)
{
	if (!c->tmpp)
	{
		ft_lstadd_back(&c->m_export, ft_lstnew(ft_strdup(p[0].cmd[j])));
		ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
		c->env_count += 1;
	}
}

void	add_to_export(t_cmds *p, t_pipe *c, int i, int j)
{
	c->tmp2 = NULL;
	c->tmpp = c->m_export;
	c->tmp3 = c->tmpp;
	if (check_if_exist(p, i, j, c) == 0 && check_for_equal(p, i, j) == 0)
		return ;
	else if (check_if_exist(p, i, j, c) == 0 && check_for_equal(p, i, j) == 1)
		return (changing_the_value(p, i, j, c), changing_the_env_v(p, i, j, c));
	if (strncmp_orginal(p[0].cmd[j], "=", 1) != 0)
	{
<<<<<<< HEAD
		while (c->tmpp)
		{
			if (strncmp_orginal(c->tmpp->content, p[0].cmd[j] , \
				ft_strlen(c->tmpp->content)) > 0)
			{	
				add_to_ex(p, c, &i, j);
=======
		// printf("change the value\n");
		changing_the_value(p, i, j, c);
		changing_the_env_v(p, i, j, c);
		return ;
	}
	if (strncmp_orginal(p[k].cmd[j], "=", 1) != 0)
	{
		while (tmp)
		{
			if (strncmp_orginal(tmp->content, p[k].cmd[j],
					ft_strlen(tmp->content)) > 0)
			{
				tmp2 = ft_lstnew(ft_strdup(p[k].cmd[j]));
				tmp2->next = tmp;
				tmp3->next = tmp2;
				c->env_count += 1;
				ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[k].cmd[j])));
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
				break ;
			}
			c->tmp3 = c->tmpp;
			c->tmpp = c->tmpp->next;
			i++;
		}
		add_to_e2(p, c, j);
	}
}

void	insert_the_node(t_cmds *p, t_pipe *c)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
<<<<<<< HEAD
	while (p[i].cmd[j] != NULL)
	{
		if (ft_strcmp(p[i].cmd[j], "=") != 0
			&& ft_isexportable(p[i].cmd[j], len_till_equal(p[i].cmd[j])) == 0)
=======
	while (p[i].cmd[j])
	{
		// printf("p = %s\n", p[i].cmd[j]);
		if (ft_strncmp(p[i].cmd[j], "=", 1) != 0)
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
			add_to_export(p, c, i, j);
		else if (ft_isexportable(p[i].cmd[j], len_till_equal(p[i].cmd[j])) == 1 \
			|| ft_strcmp(p[i].cmd[j], "=") == 0)
		{
			g_exit_code = 1;
			write (2, p[i].cmd[j], ft_strlen(p[i].cmd[j]));
			write(2, ": not a valid identifier\n", 25);
		}
		j++;
	}
}

int	check_if_exist(t_cmds *p, int i, int j, t_pipe *c)
{
	int		len;
	t_list	*t_e;

	len = len_till_equal(p[i].cmd[j]);
	t_e = c->m_export;
	while (t_e)
	{
		if (strncmp_orginal(t_e->content, p[i].cmd[j], len) == 0)
			return (0);
		t_e = t_e->next;
	}
	return (1);
}

int	len_till_equal(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	check_for_flag(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == 'n')
			j++;
		else
			return (1);
		i++;
	}
	return (0);
}
