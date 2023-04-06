/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:18:17 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/06 18:05:46 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_to_add(t_pipe *c, t_cmds *p, int i, int j)
// {
// 	printf("c = %s\n", c->tmpp->content);
// 	printf("2 = %s\n", p[0].cmd[j]);
// 	if (strncmp_orginal(c->tmpp->content, p[0].cmd[j],
// 			ft_strlen(c->tmpp->content)) > 0)
// 	{
// 		// printf("hi\n");
// 		c->tmp2 = ft_lstnew(ft_strdup(p[0].cmd[j]));
// 		c->tmp2->next = c->tmpp;
// 		if (i != 0)
// 			c->tmp3->next = c->tmp2;
// 		c->env_count += 1;
// 		ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
// 		if (i == 0)
// 			c->m_export = c->tmp2;
// 		// return (0);
// 	}
// 	// return (1);
// }

void	input_red(t_cmds *p, t_pipe *c)
{
	(void)p;
	(void)c;
}

void	output_red(t_cmds *p, t_pipe *c, char *cmd)
{
	(void)cmd;
	if (check_heredoc(p, c) == 1)
		exec_heredoc(p, c, 0);
	check_exec_redirect(p, c, 1, 0);
}

void	echo_new_line(t_cmds *p, int x, int y, t_pipe *c)
{
	(void)c;
	while (p[x].cmd[y])
	{
		printf("%s", p[x].cmd[y]);
		if (p[x].cmd[y + 1])
			printf(" ");
		y++;
	}
	printf("\n");
}

void	echo_flag(t_cmds *p, int x, int y, t_pipe *c)
{
	(void)c;
	y += 1;
	if (!p[x].cmd[y])
		return ;
	while (p[x].cmd[y + 1])
	{
		printf("%s ", p[x].cmd[y]);
		y++;
	}
	printf("%s", p[x].cmd[y]);
}

int	heredoc_condition(int fd)
{
	if (fd == 0)
		return (0);
	return (fd);
}
