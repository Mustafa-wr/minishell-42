/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:46:46 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/01 02:32:36 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing_fds(t_pipe *c)
{
	close(c->fd[0][0]);
	close(c->fd[0][1]);
	close(c->fd[1][0]);
	close(c->fd[1][1]);
}

void	close_first_pipe(t_cmds *p, t_pipe *c)
{
	close(c->fd[0][0]);
	close(c->fd[0][1]);
	if (c->j == p->cmd_len - 1)
	{
		close(c->fd[1][1]);
		close(c->fd[1][0]);
	}
	// c->i = -1;
}

void	close_second_pipe(t_pipe *c)
{
	close(c->fd[1][0]);
	close(c->fd[1][1]);
	c->i = 0;
}
