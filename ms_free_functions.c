/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:ms_free_functions.c
/*   ms_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:36:16 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/02 14:38:57 by abdamoha         ###   ########.fr       */
=======
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:19:26 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/27 15:11:53 by abdamoha         ###   ########.fr       */
>>>>>>> e9c7e44755aaf7c7d479131a17b1a69d194f0a36:ms_parse_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD:ms_free_functions.c
=======
int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

>>>>>>> e9c7e44755aaf7c7d479131a17b1a69d194f0a36:ms_parse_utils.c
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
<<<<<<< HEAD:ms_free_functions.c
	free_strings(pipe->cmds);
	free(cmd);
}
=======
	free(av);
}
>>>>>>> e9c7e44755aaf7c7d479131a17b1a69d194f0a36:ms_parse_utils.c
