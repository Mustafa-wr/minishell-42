/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/05 17:47:48 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_pipes(t_cmds *p, t_pipe *c)
{
	int		fd[2][2];
	int		i;
	int		j;
	char	*cmd_exec = NULL;

	i = 0;
	j = 0;
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
	// exit(0);
	// printf("cmd_exec = %s\n", p[i].cmd[0]);
	// // printf("e = %s\n", c->m_env->content);
	// printf("cmd_exec = %s", cmd_exec);
	// exit(0);
	int pid = fork();
	if (pid == 0)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[1][0]);
		close(fd[0][0]);
		cmd_exec = check_command_existence(p[i].cmd[0], c->m_path);
		if (execve(cmd_exec, p[i].cmd, NULL) < 0)
		{
			printf("error_execve");
			exit(0);
		}
		free(cmd_exec);
	}
	i++;
	int	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[1][0]);
		close(fd[0][0]);
		cmd_exec = check_command_existence(p[i].cmd[0], c->m_path);
		if (execve(cmd_exec, p[i].cmd, NULL) < 0)
		{
			printf("error_execve");
			exit(0);
		}
	}
	close(fd[0][1]);
	close(fd[1][1]);
	close(fd[1][0]);
	close(fd[0][0]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	// exit(0);
}
