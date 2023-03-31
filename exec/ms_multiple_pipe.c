/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/31 23:52:33 by abdamoha         ###   ########.fr       */
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
		if (check_heredoc(p, c) == 1)
			exec_heredoc(p, c, j);
		c->pid = fork();
		if (c->pid == 0)
		{
			if (j == 0)
			{
				c->fd2 = check_input_redirect(p, c);
				if (c->fd2 > 2)
				{
					printf("input\n");
					dup2(c->fd2, STDIN_FILENO);
					close(c->fd2);
				}
				dup2(c->fd[0][1], STDOUT_FILENO);
				close(c->fd[0][1]);
				close(c->fd[0][0]);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
					write(2, ": command not found\n", 21);
					free(cmd_exec);
					closing_fds(c);
					free_and_exit(c, p);
				}
			}
			else if (j == p->cmd_len - 1)
			{
				c->fd2 = check_input_redirect(p, c);
				if (c->fd2 > 2)
				{
					printf("input\n");
					dup2(c->fd2, STDIN_FILENO);
					close(c->fd2);
				}
				else
				{
					if (i % 2 == 0 && j == 1)
					{
						dup2(c->fd[0][0], STDIN_FILENO);
						closing_fds(c);
					}
					else if (i % 2 == 1)
					{
						dup2(c->fd[0][0], STDIN_FILENO);
						close(c->fd[0][1]);
						close(c->fd[0][0]);
						// closing_fds(c);
					}
					else
					{
						dup2(c->fd[1][0], STDIN_FILENO);
						close(c->fd[1][1]);
						close(c->fd[1][0]);
					}
				}
				c->fd1 = check_exec_rederict(p, c);
				if (c->fd1 > 2)
				{
					if (dup2(c->fd1, STDOUT_FILENO) == -1)
					{
						printf("same shit\n");
						exit(0);
					}
					close(c->fd1);
				}
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
					write(2, ": command not found\n", 21);
					free(cmd_exec);
					closing_fds(c);
					free_and_exit(c, p);
				}		
			}
			else
			{
				if (i % 2 == 1)
				{
					if (p[j].red_len > 0)
					{
						c->fd2 = check_input_redirect(p, c);
						if (c->fd2 > 2)
						{
							dup2(c->fd2, STDIN_FILENO);
							close(c->fd2);
						}
						else
						{
							dup2(c->fd[0][0], STDIN_FILENO);
						}
						c->fd2 = check_exec_rederict(p, c);
						if (c->fd2 > 2)
						{
							dup2(c->fd2, STDOUT_FILENO);
							close(c->fd2);
						}
						else
						{
							dup2(c->fd[1][1], STDOUT_FILENO);
						}
					}
					else
					{
						dup2(c->fd[0][0], STDIN_FILENO);
						dup2(c->fd[1][1], STDOUT_FILENO);
						close(c->fd[0][0]);
						close(c->fd[1][1]);
					}
				}
				else
				{
					if (check_heredoc(p, c) == 1)
					{
						c->fd1 = exec_heredoc(p, c, j);
						dup2(c->fd1, STDIN_FILENO);
						close(c->fd1);
					}
					c->fd2 = check_input_redirect(p, c);
					if (c->fd2 > 2)
					{
						if (check_heredoc(p, c) == 0)
							dup2(c->fd2, STDIN_FILENO);
						close(c->fd2);
					}
					else
					{
						if (check_heredoc(p, c) == 0)
							dup2(c->fd[1][0], STDIN_FILENO);
					}
					c->fd2 = check_exec_rederict(p, c);
					if (c->fd2 > 2)
					{
						dup2(c->fd2, STDOUT_FILENO);
						close(c->fd2);
					}
					else
						dup2(c->fd[0][1], STDOUT_FILENO);
				}
				closing_fds(c);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					write(2, p[0].cmd[0], ft_strlen(p[0].cmd[0]));
					write(2, ": command not found\n", 21);
					free(cmd_exec);
					closing_fds(c);
					free_and_exit(c, p);
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
}
