/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:18:17 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/29 23:08:51 by abdamoha         ###   ########.fr       */
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
	if (p[0].outs[0].flag == 0 || p[0].outs[0].flag == 3)
	{
		if (check_heredoc(p, c) == 1)
		{
			exec_heredoc(p, c, 0);
		}
		c->fd1 = check_input_redirect(p, c);
		if (c->fd1 > 2)
		{
			dup2(c->fd1, STDIN_FILENO);
			close(c->fd1);
		}
	}
}

// void	output_red(t_cmds *p, t_pipe *c, char *cmd)
// {
// 	if (p[0].outs[p[0].red_len - 1].flag == 1)
// 	{
// 		c->fd2 = check_exec_rederict(p, c);
// 		if (c->fd2 > 2)
// 		{
// 			if (cmd)
// 			{
// 				dup2(c->fd2, STDOUT_FILENO);
// 					close(c->fd2);
// 			}
// 		}
// 	}
// 	if ((!cmd && !p[0].cmd)
// 		|| (cmd == NULL && p[0].red_len > 0 && !p[0].cmd[0]))
// 	{
// 		free_and_exit(c, p);
// 	}
// 	else if (cmd == NULL && !p[0].cmd)
// 	{
// 		write(2, &p[0].cmd[0], ft_strlen(p[0].cmd[0]));
// 		write(2, "command not found :\n", 22);
// 		free_and_exit(c, p);
// 	}
// }
