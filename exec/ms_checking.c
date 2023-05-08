/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:18:17 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/24 18:49:30 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_red(t_cmds *p, t_pipe *c, char *cmd)
{
	(void)cmd;
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

void	print_error(int i, int j, t_cmds *p)
{
	write(2, p[i].cmd[j], ft_strlen(p[i].cmd[j]));
	write (2, " : not a valid identifier\n", 26);
}
