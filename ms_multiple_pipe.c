/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/08 23:30:27 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_pipes(t_cmds *p, t_pipe *c)
{
	int		fd[2][2];
	int		i;
	int		k;
	int		j;
	char	*cmd_exec = NULL;

	i = 0;
	j = 0;
	k = 0;
	// printf("jkghfjyhfjhf");
	while (i < 2)
	{
		pipe(fd[i]);
		if (fd[i][0] < 0 || fd[i][1] < 0)
		{
			printf("pipe error\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	printf("cmdlen = %d\n", p->cmd_len);
	while (j < p->cmd_len)
	{
		c->pid = fork();
		if (c->pid == 0)
		{
			if (j == 0)
			{
				printf("first\n");
				dup2(fd[0][1], STDOUT_FILENO);
				close(fd[0][1]);
				close(fd[1][1]);
				close(fd[1][0]);
				close(fd[0][0]);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					printf("error_execve");
					exit(0);
				}
				// free(cmd_exec);
			}
			else if (j == p->cmd_len - 1)
			{
				printf("last");
				printf("i in = %d\n", i);
				if (i == 0)
				{
					printf("1\n");
					dup2(fd[i + 1][i], STDIN_FILENO);
				}
				else if (j == 1)
				{
					printf("2\n");
					dup2(fd[i - 1][i - 1], STDIN_FILENO);
				}
				else
				{
					printf("3\n");
					dup2(fd[i - 1][i - 1], STDIN_FILENO);
				}
				close(fd[0][1]);
				close(fd[1][1]);
				close(fd[1][0]);
				close(fd[0][0]);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				// printf("cmd = %s\n", cmd_exec);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					printf("error_execve");
					exit(0);
				}
			}
			else
			{
				printf("middle\n");
				if (i == 0)
				{
					printf("m1\n");
					dup2(fd[i + 1][i], STDIN_FILENO);
					dup2(fd[i][i + 1], STDOUT_FILENO);
				}
				else
				{
					printf("m2\n");
					dup2(fd[i - 1][i - 1], STDIN_FILENO);
					dup2(fd[i][i], STDOUT_FILENO);
				}
				close(fd[0][1]);
				close(fd[1][1]);
				close(fd[1][0]);
				close(fd[0][0]);
				cmd_exec = check_command_existence(p[j].cmd[0], c->m_path);
				if (execve(cmd_exec, p[j].cmd, NULL) < 0)
				{
					printf("error_execve");
					exit(0);
				}
			}
			free(cmd_exec);
		}
		if (i == 1)
		{
			printf("be zero");
			close(fd[0][1]);
			close(fd[0][0]);
			pipe(fd[0]);
			i = 0;
		}
		else
			i++;
		printf("i = %d\n", i);
		// while (k < p->cmd_len)
		// {
		// 	wait(NULL);
		// 	k++;
		// }
		// close(fd[0][0]);
		// close(fd[0][1]);
		// pipe(fd[0]);
		j++;
		// i++;
	}
	k = 0;
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	while (k < p->cmd_len)
	{
		wait(NULL);
		k++;
	}
	// waitpid(pid, NULL, 0);
	// waitpid(pid2, NULL, 0);
	// waitpid(pid3, NULL, 0);
	// waitpid(pid4, NULL, 0);
	// wait(NULL);
	// wait(NULL);
	// wait(NULL);
	// wait(NULL);
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	dup2(fd[0][1], STDOUT_FILENO);
	// 	close(fd[0][1]);
	// 	close(fd[1][1]);
	// 	close(fd[1][0]);
	// 	close(fd[0][0]);
	// 	cmd_exec = check_command_existence(p[i].cmd[0], c->m_path);
	// 	if (execve(cmd_exec, p[i].cmd, NULL) < 0)
	// 	{
	// 		printf("error_execve");
	// 		exit(0);
	// 	}
	// 	free(cmd_exec);
	// }
	// i++;
	// int	pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	dup2(fd[0][0], STDIN_FILENO);
	// 	dup2(fd[1][1], STDOUT_FILENO);
	// 	close(fd[0][1]);
	// 	close(fd[1][1]);
	// 	close(fd[1][0]);
	// 	close(fd[0][0]);
	// 	cmd_exec = check_command_existence(p[i].cmd[0], c->m_path);
	// 	if (execve(cmd_exec, p[i].cmd, NULL) < 0)
	// 	{
	// 		printf("error_execve");
	// 		exit(0);
	// 	}
	// }
	// i++;
	// close(fd[0][0]);
	// close(fd[0][1]);
	// pipe(fd[0]);
	// if (fd[0][1] < 0 || fd[0][1] < 0)
	// {
	// 	printf("error");
	// 	exit(0);
	// }
	// int	pid3 = fork();
	// if (pid3 == 0)
	// {
	// 	dup2(fd[1][0], STDIN_FILENO);
	// 	dup2(fd[0][1], STDOUT_FILENO);
	// 	close(fd[0][1]);
	// 	close(fd[1][1]);
	// 	close(fd[1][0]);
	// 	close(fd[0][0]);
	// 	cmd_exec = check_command_existence(p[i].cmd[0], c->m_path);
	// 	if (execve(cmd_exec, p[i].cmd, NULL) < 0)
	// 	{
	// 		printf("error_execve");
	// 		exit(0);
	// 	}
	// }
	// i++;
	// int	pid4 = fork();
	// if (pid4 == 0)
	// {
	// 	dup2(fd[0][0], STDIN_FILENO);
	// 	close(fd[0][1]);
	// 	close(fd[1][1]);
	// 	close(fd[1][0]);
	// 	close(fd[0][0]);
	// 	cmd_exec = check_command_existence(p[i].cmd[0], c->m_path);
	// 	if (execve(cmd_exec, p[i].cmd, NULL) < 0)
	// 	{
	// 		printf("error_execve");
	// 		exit(0);
	// 	}
	// }
	// exit(0);
}
