/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/16 03:59:21 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multiple_pipes(t_cmds *p, t_pipe *c)
{
	int		i;
	int		k;
	int		j;
	char	*cmd_exec = NULL;

	i = 0;
	j = 0;
	k = 0;
	i = 0;
	while (j < p->cmd_len)
	{
		if (i % 2 == 0 || i == 0)
			pipe(c->fd[0]);
		else if (i % 2 == 1)
			pipe(c->fd[1]);
		c->pid = fork();
		if (c->pid == 0)
		{
			if (j == 0)
			{
				dup2(c->fd[0][1], STDOUT_FILENO);
				close(c->fd[0][1]);
				close(c->fd[0][0]);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					perror("error_execve");
					exit(1);
				}
			}
			else if (j == p->cmd_len - 1)
			{
				if (i % 2 == 0 && j == 1)
				{
					dup2(c->fd[0][0], STDIN_FILENO);
					close(c->fd[0][1]);
					close(c->fd[0][0]);
					close(c->fd[1][1]);
					close(c->fd[1][0]);
				}
				else if (i % 2 == 1)
				{
					dup2(c->fd[0][0], STDIN_FILENO);
					close(c->fd[0][1]);
					close(c->fd[0][0]);
				}
				else
				{
					dup2(c->fd[1][0], STDIN_FILENO);
					close(c->fd[1][1]);
					close(c->fd[1][0]);
				}
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					perror("error_execve");
					exit(1);
				}		
			}
			else
			{
				if (i % 2 == 1)
				{
					dup2(c->fd[0][0], STDIN_FILENO);
					dup2(c->fd[1][1], STDOUT_FILENO);
				}
				else
				{
					dup2(c->fd[1][0], STDIN_FILENO);
					dup2(c->fd[0][1], STDOUT_FILENO);
				}
				closing_fds(c);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					perror("error_execve");
					exit(1);
				}
			}
		}
		if (i % 2 == 1 && i != 0)
		{
			close(c->fd[0][0]);
			close(c->fd[0][1]);
			if (j == p->cmd_len - 1)
			{
				close(c->fd[1][1]);
				close(c->fd[1][0]);
			}
			i = -1;
		}
		else if (i % 2 == 0 && j != 0)
		{
			close(c->fd[1][0]);
			close(c->fd[1][1]);
			i = 0;
		}
		i++;
		j++;
	}
	k = 0;
	closing_fds(c);
	while (k < p->cmd_len)
	{
		wait(NULL);
		k++;
	}
	free_all(c, p);
	free_strings(c->m_path);
}
