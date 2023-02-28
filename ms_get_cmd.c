/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:12:04 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/28 21:50:34 by mradwan          ###   ########.fr       */
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
	
	str = malloc(sizeof(char) * (ft_strlen(s) - (len - start)) + 2);
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
	free(s);
    return (str);
}

void	files_fellings(t_pipe *pipe, t_cmds *cmds, t_vars *var)
{
	var->start = var->x - 1;
	if (pipe->cmds[var->j][var->x + 1] == '>' || pipe->cmds[var->j][var->x + 1] == '<')
	{
		if(pipe->cmds[var->j][var->x + 1] == '>')
			cmds[var->j].outs[var->xy].flag = APPEND_OUT;
		else if (pipe->cmds[var->j][var->x + 1] == '<')
			cmds[var->j].outs[var->xy].flag = APPEND_IN;
		var->x = var->x + 2;
	}
	else if (pipe->cmds[var->j][var->x] == '>')
	{
		cmds[var->j].outs[var->xy].flag = IN_FILE;
		var->x++;
	}
	else if (pipe->cmds[var->j][var->x] == '<')
	{
		cmds[var->j].outs[var->xy].flag = OUT_FILE;
		var->x++;
	}
}

void	files_saving(t_pipe *pipe, t_cmds *cmds)
{
	int	i;
	// char *tmp;
	t_vars var;
	int h = 0;

	var.start = 0;
	var.quote_char = 0;
	i = 0;
	var.j = 0;
	var.x = 0;
	while (pipe->cmds[i])
		i++;
	cmds = malloc(sizeof(t_cmds) * i);
	while (var.j < i)
	{
		cmds[var.j].red_len = num_of_redirects(pipe->cmds[var.j]);
		cmds[var.j].outs = malloc(sizeof(t_redirect) * cmds[var.j].red_len);
		var.xy = 0;
		var.x = 0;
		while (pipe->cmds[var.j][var.x])
		{
			if (pipe->cmds[var.j][var.x] == '"' || pipe->cmds[var.j][var.x] == '\'')
			{
				if (var.quote_char == 0)
					var.quote_char = pipe->cmds[var.j][var.x];
				else if (var.quote_char == pipe->cmds[var.j][var.x])
					var.quote_char = 0;
			}
			if ((pipe->cmds[var.j][var.x] == '>' || pipe->cmds[var.j][var.x] == '<') \
				&& is_between_quotes(pipe->cmds[var.j], var.x) && !var.quote_char)
			{
				files_fellings(pipe, cmds, &var);
				store_the_file_name(pipe->cmds[var.j], &cmds[var.j].outs[var.xy].file_name, var.x + 1, &var);
				// printf("flag	  : %d\n", var.i);
				// pipe->cmds[var.j] = remove_substr(pipe->cmds[var.j], var.start, var.i);
				pipe->cmds[var.j] = remove_substr(pipe->cmds[var.j], var.start, var.i);
				var.x = var.start - 1;
				// printf("file name : %s\n", pipe->cmds[var.j]);
				// printf("file name : %s\n", cmds[var.j].outs[var.xy].file_name);
				// printf("flag	  : %d\n", cmds[var.j].outs[var.xy].flag);
				var.xy++;
			}
			// else
			// 	tmp = remove_substr(pipe->cmds[var.j], 0, ft_strlen(tmp));
			var.x++;
		}
		cmds[var.j].cmd = ft_split(pipe->cmds[var.j], ' ');
		while (cmds[var.j].cmd[h])
			clean_quotes(cmds[var.j].cmd[h++]);
		// h = 0;
		// while (cmds[var.j].cmd[h])
		// 	puts(cmds[var.j].cmd[h++]);
		var.j++;
	}
}
