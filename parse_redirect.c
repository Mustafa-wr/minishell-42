/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:53:42 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/16 17:55:47 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(t_pipe *cmd, int j, int in_quotes, int in_d_quotes)
{
	if (cmd->cmds[j][cmd->i] == '>' || cmd->cmds[j][cmd->i] == '<' || \
		(cmd->cmds[j][cmd->i] == '>' && cmd->cmds[j][cmd->i + 1] == '>') \
			|| (cmd->cmds[j][cmd->i] == '<' && cmd->cmds[j][cmd->i + 1] == '<'))
	{
		cmd->i++;
		if ((cmd->cmds[j][cmd->i] == '<' && cmd->cmds[j][cmd->i - 1] == '<') \
			|| (cmd->cmds[j][cmd->i] == '>' && cmd->cmds[j][cmd->i - 1] == '>'))
			cmd->i++;
		while (cmd->cmds[j][cmd->i] == ' ')
			cmd->i++;
		if ((cmd->cmds[j][cmd->i] == '>' || cmd->cmds[j][cmd->i] == '<') \
			&& (!in_quotes && !in_d_quotes))
			return (0);
		while (cmd->cmds[j][cmd->i] == ' ')
			cmd->i++;
		if (cmd->cmds[j][cmd->i] == '\0')
		{
			free_strings(cmd->cmds);
			// free_strings(cmd->env->path);
			return (0);
		}
	}
	return (1);
}

static int	check_from_back(char *s)
{
	int	i;

	i = ft_strlen(s);
	i--;
	while (s[i] == ' ')
		i--;
	if (s[i] == '>' || s[i] == '<')
		return (0);
	return (1);
}

static int	redirect_helper(t_pipe *cmd, int j, int in_quotes, int in_d_quotes)
{
	if (!check_from_back(cmd->cmds[j]))
		return (0);
	cmd->i = 0;
	while (cmd->cmds[j][cmd->i])
	{
		if (cmd->cmds[j][cmd->i] == '\'')
		{
			if (!in_quotes)
				in_quotes = 1;
			else
				in_quotes = 0;
		}
		if (cmd->cmds[j][cmd->i] == '\"')
		{
			if (!in_d_quotes)
				in_d_quotes = 1;
			else
				in_d_quotes = 0;
		}
		if (!is_redirect(cmd, j, in_quotes, in_d_quotes))
			return (0);
		cmd->i++;
	}
	return (1);
}

int	check_redirect(t_pipe *cmd)
{
	int	j;
	int	in_quotes;
	int	in_d_quotes;

	cmd->i = 0;
	j = 0;
	in_d_quotes = 0;
	in_quotes = 0;
	while (cmd->cmds[j])
	{
		if (!redirect_helper(cmd, j, in_quotes, in_d_quotes))
			return (0);
		j++;
	}
	int i = 0;
	while (cmd->cmds[i])
		clean_quotes(cmd->cmds[i++]);
	i = 0;
	while (cmd->cmds[i])
		printf("%s\n", cmd->cmds[i++]);
	return (1);
}