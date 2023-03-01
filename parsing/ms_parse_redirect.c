/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:53:42 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/01 19:50:01 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (0);
	}
	return (1);
}

// static int	the_redirect_is_between_q(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] == '"' || str[i] == '\'') && str[i + 1])
// 		{
// 			i++;
// 			while ((str[i] == ' ' || str[i] == '\t') && str[i + 1])
// 				i++;
// 			if (str[i] == '>' || str[i] == '<')
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static int	check_from_back(char *s)
{
	int	i;

	i = ft_strlen(s);
	if(i)
		i--;
	while (s[i] == ' ' && i > 0)
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
	int	i;
	int	in_quotes;
	int	in_d_quotes;

	cmd->i = 0;
	j = 0;
	in_d_quotes = 0;
	in_quotes = 0;
	while (cmd->cmds[j])
	{
		if (!redirect_helper(cmd, j, in_quotes, in_d_quotes))
			return (free_strings(cmd->cmds), 0);
		j++;
	}
	i = 0;
	while (cmd->cmds[i])
		i++;
	cmd->num_of_pipes = i;
	j = 0;
	// int b = 0;
	// cmd->ibq = malloc(sizeof(int) * OPEN_MAX);
	// cmd->args = malloc(sizeof(char **) * i * 3 + 1);
	// i = 0;
	// while (cmd->cmds[i])
	// {
	// 	j = 0;
	// 	cmd->args[i] = ft_split(cmd->cmds[i], ' ');
	// 	while (cmd->args[i][j])
	// 	{
	// 		// puts(cmd->args[i][j]);
	// 		cmd->ibq[b] = the_redirect_is_between_q(cmd->args[i][j]);
	// 		clean_quotes(cmd->args[i][j]);
	// 		// printf("the value is %d\n", cmd->ibq[b]);
	// 		// printf("%s\n", cmd->args[i][j]);
	// 		j++;
	// 		b++;
	// 	}
	// 	// printf("\n");
	// 	i++;
	// }
	// cmd->args[i] = NULL;
	// free_3d(cmd->args);
	return (1);
}
