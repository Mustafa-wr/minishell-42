/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:44:06 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/28 04:00:14 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_heredoc(t_cmds *p, t_pipe *c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	c->fd1 = 0;
	while (j < p->cmd_len)
	{
		i = 0;
		while (i < p[j].red_len)
		{
			if (p[j].outs[i].flag == 3)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

void	exec_heredoc(t_cmds *p, t_pipe *c)
{
	// int		i = 0;
	int		tmp = 0;
	char	*line;

	(void)p;
	c->fd1 = 0;
	// m = c->tmpfile;
	char *m = "h";
	printf("m = %s\n", m);
	printf("heredoc\n");
	tmp = open(m, O_RDWR | O_TRUNC, 0644);
	if (tmp < 0)
	{
		printf("error\n");
		exit(1);
	}
	printf("tmp = %d\n", tmp);
	c->fd1 = open("s", O_WRONLY | O_APPEND, 0644);
	if (c->fd1 == -1)
	{
		perror("open");
		return ;
	}
	write(1, "> ", 2);
	line = get_next_line(0);
	while (ft_strncmp(line, p[0].outs[0].file_name, ft_strlen(p[0].outs[0].file_name)) != 0)
	{
		ft_putstr_fd(line, tmp);
		write(1, "> ", 2);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(tmp);
	tmp = open(m, O_RDONLY);
	// line = NULL;
	// line = get_next_line(tmp);
	// while (line)
	// {
	// 	// printf("line = %s", line);
	// 	free(line);
	// 	line = get_next_line(tmp);
	// }
	int n = fork();
	if (n == 0)
	{
		// printf("hi\n");
		update_env(c);
		get_path(c->tmp_env, c);
		dup2(tmp, STDIN_FILENO);
		char *cmd = check_command_existence(p[0].cmd[0], c->m_path);
		if (execve(cmd, p[0].cmd, c->tmp_env) < 0)
		{
			printf("error\n");
			free_and_exit(c, p);
		}
	}
	waitpid(n, NULL , 0);
	close(tmp);
	close(c->fd1);
}
