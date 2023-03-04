/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:53:42 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/04 19:29:53 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirect(t_pipe *cmd, t_vars *v)
{
	if (cmd->cmds[v->j][cmd->i] == '>' || cmd->cmds[v->j][cmd->i] == '<')
	{
		cmd->i++;
		if ((cmd->cmds[v->j][cmd->i] == '<' && \
			cmd->cmds[v->j][cmd->i - 1] == '<') \
			|| (cmd->cmds[v->j][cmd->i] == '>' && \
				cmd->cmds[v->j][cmd->i - 1] == '>'))
			cmd->i++;
		while (cmd->cmds[v->j][cmd->i] == ' ')
			cmd->i++;
		if ((cmd->cmds[v->j][cmd->i] == '>' || cmd->cmds[v->j][cmd->i] == '<') \
			&& (!v->in_quotes))
			return (0);
		while (cmd->cmds[v->j][cmd->i] == ' ')
			cmd->i++;
		if (cmd->cmds[v->j][cmd->i] == '\0')
			return (0);
	}
	else
		cmd->i++;
	return (1);
}

static int	check_from_back(char *s)
{
	int	i;

	i = ft_strlen(s);
	if (i)
		i--;
	while (s[i] == ' ' && i > 0)
		i--;
	if (s[i] == '>' || s[i] == '<')
		return (0);
	return (1);
}

static int	redirect_helper(t_pipe *cmd, t_vars *vars)
{
	if (!check_from_back(cmd->cmds[vars->j]))
		return (0);
	cmd->i = 0;
	while (cmd->cmds[vars->j][cmd->i])
	{
		if (cmd->cmds[vars->j][cmd->i] == '\'' || \
			cmd->cmds[vars->j][cmd->i] == '\"')
		{
			if (!vars->in_quotes)
				vars->in_quotes = cmd->cmds[vars->j][cmd->i];
			else if (vars->in_quotes == cmd->cmds[vars->j][cmd->i])
				vars->in_quotes = 0;
		}
		if (!is_redirect(cmd, vars))
			return (0);
	}
	return (1);
}

int	check_redirect(t_pipe *cmd)
{
	t_vars	vars;

	cmd->i = 0;
	vars.j = 0;
	vars.in_d_quotes = 0;
	vars.in_quotes = 0;
	while (cmd->cmds[vars.j])
	{
		if (!redirect_helper(cmd, &vars))
			return (free_strings(cmd->cmds), 0);
		vars.j++;
	}
	return (1);
}
