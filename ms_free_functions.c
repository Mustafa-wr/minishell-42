/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:36:16 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/25 12:41:48 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	if (av)
	{
		free(av);
		av = NULL;
	}
}

static void	free_condition(int i, int j, t_cmds *cmd)
{
	free(cmd[i].outs[j].file_name);
	cmd[i].outs[j].file_name = NULL;
}

void	free_all(t_pipe *pipe, t_cmds *cmd)
{
	pipe->i = -1;
	pipe->j = -1;
	while (++pipe->i < pipe->cmd_len)
	{
		pipe->j = -1;
		if (cmd[pipe->i].red_len > 0)
		{
			while (++pipe->j < cmd[pipe->i].red_len)
				if (cmd[pipe->i].outs[pipe->j].file_name)
					free_condition(pipe->i, pipe->j, cmd);
			if (cmd[pipe->i].outs)
			{
				free(cmd[pipe->i].outs);
				cmd[pipe->i].outs = NULL;
			}
		}
		free_strings(cmd[pipe->i].cmd);
	}
	free_strings(pipe->cmds);
	pipe->cmds = NULL;
	free(cmd);
	cmd = NULL;
}
