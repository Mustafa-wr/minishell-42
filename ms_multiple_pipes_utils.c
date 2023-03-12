/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:46:46 by abdamoha          #+#    #+#             */
/*   Updated: 2023/03/12 16:34:49 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closing_fds(t_pipe *c)
{
	close(c->fd[0][0]);
	close(c->fd[0][1]);
	close(c->fd[1][0]);
	close(c->fd[1][1]);
}
