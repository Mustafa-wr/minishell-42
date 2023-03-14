/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:36:16 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/12 21:32:01 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strings(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	free_all(t_pipe *pipe, t_cmds *cmd)
{
	int i = 0;
	int j = 0;
	while (i < pipe->cmd_len)
	{
		j = 0;
		if(cmd[i].red_len > 0)
		{
			while (j < cmd[i].red_len)
			{
				if (cmd[i].outs[j].file_name)
				{
					free(cmd[i].outs[j].file_name);
				}
				j++;
			}
			if(cmd[i].outs)
				free(cmd[i].outs);
		}
		free_strings(cmd[i].cmd);
		i++;
	}
	free_strings(pipe->cmds);
	free(cmd);
}