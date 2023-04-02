/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:18:17 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/02 21:48:42 by abdamoha         ###   ########.fr       */
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
	c->t = 0;
	if (input_check(p, c) == 1)
	{
		if (check_heredoc(p, c) == 1)
			exec_heredoc(p, c, 0);
		c->t = check_input_redirect(p, c, 1, 0);
		if (c->t > 2)
		{
			if (dup2(c->t, STDIN_FILENO) == -1)
			{
				printf("kkkk\n");
				exit(EXIT_FAILURE);
			}
			close(c->t);
		}
	}
}

void	output_red(t_cmds *p, t_pipe *c, char *cmd)
{
	if (output_check(p, c) == 1)
	{
		c->fd2 = check_exec_rederict(p, c, 1, 0);
		printf("c = %d\n", c->fd2);
		if (c->fd2 > 2)
		{
			if (cmd)
			{
				if (dup2(c->fd2, STDOUT_FILENO) == -1)
				{
					printf("same shit\n");
					exit(EXIT_FAILURE);
				}
				close(c->fd2);
			}
		}
		return ;
	}
	if ((!cmd && !p[0].cmd)
		|| (cmd == NULL && p[0].red_len > 0 && !p[0].cmd[0]))
	{
		free_and_exit(c, p);
	}
	else if (cmd == NULL && !p[0].cmd)
	{
		write(2, &p[0].cmd[0], ft_strlen(p[0].cmd[0]));
		write(2, "command not found :\n", 22);
		free_and_exit(c, p);
	}

}

void	echo_new_line(t_cmds *p, int x, int y, t_pipe *c)
{
	while (p[x].cmd[y])
	{
		if (p[x].red_len == 0)
		{
			printf("%s", p[x].cmd[y]);
			if (p[x].cmd[y + 1])
				printf(" ");
		}
		else
		{
			write_in_fd(p, x, y, c);
			write(c->fd1, "\n", 1);
			close(c->fd1);
			return ;
		}
		y++;
	}
	printf("\n");
}

void	echo_flag(t_cmds *p, int x, int y, t_pipe *c)
{
	y += 1;
	if (!p[x].cmd[y])
		return ;
	while (p[x].cmd[y + 1])
	{
		if (c->fd1 > 2)
		{
			write_in_fd(p, x, y, c);
			close(c->fd1);
			return ;
		}
		else
			printf("%s ", p[x].cmd[y]);
		y++;
	}
	if (c->fd1 > 2)
	{
		write_in_fd(p, x, y, c);
		close(c->fd1);
		return ;
	}
	else
		printf("%s", p[x].cmd[y]);
}

int	heredoc_condition(int fd)
{
	if (fd == 0)
	{
		// close(fd);
		return (0);
	}
	return (fd);
}
