/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:21:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/11 23:51:01 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_string_helper(char *str, int in_quote, int in_d_quote, int i)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (in_quote)
				in_quote = 0;
			else if (!in_d_quote)
				in_quote = 1;
		}
		else if (str[i] == '\"')
		{
			if (in_d_quote)
				in_d_quote = 0;
			else if (!in_quote)
				in_d_quote = 1;
		}
		i++;
	}
	if (in_quote || in_d_quote)
		return (0);
	return (1);
}

static int	check_string(char *str)
{
	int	i;
	int	in_quote;
	int	in_d_quote;

	i = 0;
	in_quote = 0;
	in_d_quote = 0;
	if (!check_string_helper(str, in_quote, in_d_quote, i))
		return (0);
	return (1);
}

static int	pipe_from_back(char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	if (!len)
		return (1);
	len--;
	while ((line[len] == ' ' || line[len] == '\t') && len > 0)
		len--;
	if (line[len] == '|')
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '|')
		return (0);
	return (1);
}

static int	check_pipe_in_quotes(char *line, int i, int quotes, int j)
{
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (quotes == 0)
				quotes = line[i];
			else if (!quotes)
				quotes = 0;
			i++;
			continue ;
		}
		if (line[i] == '|' && !quotes)
		{
			j = i + 1;
			while (line[j] == ' ' || line[j] == '\t')
				j++;
			if (line[j] == '\0' || line[j] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_pipes(t_pipe *pipe, char *line, t_cmds *cmds)
{
	int	i;
	int	j;
	int	quotes;

	(void)cmds;
	quotes = 0;
	i = 0;
	j = 0;
	if (!pipe_from_back(line))
		return (0);
	if (!check_pipe_in_quotes(line, i, quotes, j))
		return (0);
	if (!check_string(line))
		return (0);
	pipe->cmds = ft_split(line, '|');
	i = 0;
	while (pipe->cmds[i])
	{
		dollar_expansion(&pipe->cmds[i], pipe);
		pipe->cmds[i] = ft_add_spaces(pipe->cmds[i]);
		replace_spaces_tabs(pipe->cmds[i]);
		// clean_quotes(pipe->cmds[i]);
		// printf("%s\n", pipe->cmds[i]);
		i++;
	}
	pipe->cmd_len = i;
	return (1);
}
