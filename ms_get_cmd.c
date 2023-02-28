/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:12:04 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/28 16:41:44 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_of_redirects(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			num++;
		}
		i++;
	}
	return (num);
}

void	store_the_file_name(char *str, char **file_name, int i)
{
	int start;
	int	in_quote;
	int	in_d_quote;

	start = i;
	in_quote = 0;
	in_d_quote = 0;
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
		while ((str[i] && str[i] != ' ') || (str[i] && (in_d_quote || in_quote)))
			i++;
		if(str[i])
			i++;
	}
	// while (str[i] && str[i] != ' ')
	// 	i++;
	(*file_name) = ft_substr(str, start, i - start);
}

int	is_between_quotes(char *str, int x)
{
	while (str[x] && (str[x] == ' ' || str[x] == '\t'))
		x--;
	if(str[x == '\'' || str[x] == '"'])
		return (1);
	return (0);
}

void	files_saving(t_pipe *pipe, t_cmds	*cmds)
{
	int	i;
	int j;
	int xy;

	i = 0;
	j = 0;
	int x = 0;
	while (pipe->cmds[i])
		i++;
	cmds = malloc(sizeof(t_cmds) * i);
	while (j < i)
	{
		cmds[j].red_len = num_of_redirects(pipe->cmds[j]);
		cmds[j].outs = malloc(sizeof(t_redirect) * cmds[j].red_len);
		xy = 0;
		x = 0;
		while (pipe->cmds[j][x])
		{
			if ((pipe->cmds[j][x] == '>' || pipe->cmds[j][x] == '<') \
				&& is_between_quotes(pipe->cmds[j], x))
			{
				if (pipe->cmds[j][x + 1] == '>' || pipe->cmds[j][x + 1] == '<')
				{
					if(pipe->cmds[j][x + 1] == '>')
						cmds[j].outs[xy].flag = APPEND_OUT;
					else if (pipe->cmds[j][x + 1] == '<')
						cmds[j].outs[xy].flag = APPEND_IN;
					x = x + 2;
				}
				else if (pipe->cmds[j][x] == '>')
				{
					cmds[j].outs[xy].flag = IN_FILE;
					x++;
				}
				else if (pipe->cmds[j][x] == '<')
				{
					cmds[j].outs[xy].flag = OUT_FILE;
					x++;
				}
				store_the_file_name(pipe->cmds[j], &cmds[j].outs[xy].file_name, x + 1);
				printf("file name : %s\n", cmds[j].outs[xy].file_name);
				xy++;
			}
			x++;
		}
		j++;
	}
}

// if (strcmp(token, "<") == 0)
// 			{
// 				flag = IN_FILE;
// 				file_name = strtok_r(NULL, token_delim, &save_token_ptr);
// 			}
// 			else if (strcmp(token, ">") == 0)
// 			{
// 				flag = OUTFILE;
// 				file_name = strtok_r(NULL, token_delim, &save_token_ptr);
// 			}
// 			else if (strcmp(token, ">>") == 0)
// 			{
// 				flag = APPEND_OUT;
// 				file_name = strtok_r(NULL, token_delim, &save_token_ptr);
// 			}
// 			else if (strcmp(token, "<<") == 0)
// 			{
// 				flag = APPEND_IN;
// 				file_name = strtok_r(NULL, token_delim, &save_token_ptr);
// 			}
