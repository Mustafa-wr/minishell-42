/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:45:28 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/02 03:06:44 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	builtins_pipes(t_cmds *p, t_pipe *c, int fd, int j)
{
	if (p[j].cmd)
	{
		if (ft_strncmp(p[j].cmd[0], "exit", 4) == 0)
			return (ft_exit(c, p), 0);
		else if (ft_strncmp(p[j].cmd[0], "cd", 2) == 0)
			return (ft_cd(p, j, 0, c), 0);
		else if (ft_strncmp(p[j].cmd[0], "export", 6) == 0)
			return (ft_export(c, p, j, fd), 0);
		else if (ft_strncmp(p[j].cmd[0], "unset", 5) == 0)
			return (ft_unset(p, j, 0, c), 0);
		else
		{
			ft_tolower(p[j].cmd[0]);
			if (ft_strncmp(p[j].cmd[0], "echo", 4) == 0)
				return (ft_echo(p, j, 0, c), 0);
			else if (ft_strncmp(p[j].cmd[0], "pwd", 3) == 0)
				return (ft_pwd(p, c, fd), 0);
			else if (ft_strncmp(p[j].cmd[0], "env", 3) == 0)
				return (ft_env(p, c, fd), 0);
		}
	}
	// write(2, "im out \n", 9);
	return (1);
}