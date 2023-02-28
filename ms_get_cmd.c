/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:12:04 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/28 20:49:13 by mradwan          ###   ########.fr       */
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

void	store_the_file_name(char *str, char **file_name, int i, t_vars *var)
{
	int start;
	int	in_quote;

	start = i;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!in_quote)
				in_quote = str[i];
			else if (in_quote == str[i])
				in_quote = 0;
		}
		if (str[i] == ' ' && !in_quote)
			break;
		i++;
	}
	var->i = i;
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


char *remove_substr(char *s, unsigned int start, size_t len)
{
	// printf("start :%d\n", start);
	// printf("len :%zu\n", len);
	size_t	i;
	size_t	j;
    char *str;
	
	str = malloc(sizeof(char) * (ft_strlen(s) - (len - start)) + 1);
    if (!str || !s)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (i < start || i >= len)
        {
            str[j] = s[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
    return (str);
}

void	files_saving(t_pipe *pipe, t_cmds *cmds)
{
	int	i;
	int j;
	int xy;
	t_vars var;

	int quote_char = 0;
	i = 0;
	j = 0;
	int start = 0;
	int x = 0;
	char *tmp;
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
			if (pipe->cmds[j][x] == '"' || pipe->cmds[j][x] == '\'')
			{
				if (quote_char == 0)
					quote_char = pipe->cmds[j][x];
				else if (quote_char == pipe->cmds[j][x])
					quote_char = 0;
			}
			if ((pipe->cmds[j][x] == '>' || pipe->cmds[j][x] == '<') \
				&& is_between_quotes(pipe->cmds[j], x) && !quote_char)
			{
				start = x - 1;
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
				store_the_file_name(pipe->cmds[j], &cmds[j].outs[xy].file_name, x + 1, &var);
				// printf("flag	  : %d\n", var.i);
				// pipe->cmds[j] = remove_substr(pipe->cmds[j], start, var.i);
				tmp = remove_substr(pipe->cmds[j], start, var.i);
				// printf("file name : %s\n", pipe->cmds[j]);
				// printf("file name : %s\n", cmds[j].outs[xy].file_name);
				// printf("flag	  : %d\n", cmds[j].outs[xy].flag);
				xy++;
			}
			x++;
		}
		cmds[j].cmd = ft_split(tmp, ' ');
		// printf("file name : %s\n", cmds[j].cmd[0]);
		// printf("file name : %s\n", cmds[j].cmd[1]);
		j++;
	}
}
