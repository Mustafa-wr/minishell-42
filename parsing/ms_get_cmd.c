/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:12:04 by mradwan           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 19:32:44 by mradwan          ###   ########.fr       */
=======
/*   Updated: 2023/03/13 21:31:25 by mradwan          ###   ########.fr       */
>>>>>>> 09eb4cff4c04190af80726221878a5b3423b8508
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_the_file_name(char *str, char **file_name, int i, t_vars *var)
{
	int	start;
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
		if ((str[i] == ' ' || str[i] == '\t') && !in_quote)
			break ;
		i++;
	}
	var->i = i;
	(*file_name) = ft_substr(str, start, i - start);
}

void	files_fillings(t_pipe *pipe, t_cmds *cmds, t_vars *var)
{
	var->start = var->x - 1;
	if (pipe->cmds[var->j][var->x + 1] == '>' \
		|| pipe->cmds[var->j][var->x + 1] == '<')
	{
		if (pipe->cmds[var->j][var->x + 1] == '>')
			cmds[var->j].outs[var->xy].flag = APPEND;
		else if (pipe->cmds[var->j][var->x + 1] == '<')
			cmds[var->j].outs[var->xy].flag = HERE_DOC;
		var->x = var->x + 2;
	}
	else if (pipe->cmds[var->j][var->x] == '>')
	{
		cmds[var->j].outs[var->xy].flag = OUT_FILE;
		var->x++;
	}
	else if (pipe->cmds[var->j][var->x] == '<')
	{
		cmds[var->j].outs[var->xy].flag = IN_FILE;
		var->x++;
	}
}

void	utils_saving(t_pipe *pipe, t_cmds *cmds, t_vars *v)
{
	v->xy = 0;
	v->x = -1;
	while (pipe->cmds[v->j][++v->x])
	{
		if (pipe->cmds[v->j][v->x] == '"' || pipe->cmds[v->j][v->x] == '\'')
		{
			if (v->quote_char == 0)
				v->quote_char = pipe->cmds[v->j][v->x];
			else if (v->quote_char == pipe->cmds[v->j][v->x])
				v->quote_char = 0;
		}
		if ((pipe->cmds[v->j][v->x] == '>' || \
			pipe->cmds[v->j][v->x] == '<') && !v->quote_char)
		{
			files_fillings(pipe, cmds, v);
			store_the_file_name(pipe->cmds[v->j], \
				&cmds[v->j].outs[v->xy].file_name, v->x + 1, v);
			clean_quotes(cmds[v->j].outs[v->xy].file_name);
			remove_substr(pipe->cmds[v->j], v->start, v->i);
			v->x = v->start - 1;
			v->xy++;
		}
	}
}

void	files_saving(t_pipe *pipe, t_cmds **tmp)
{
	t_cmds	*cmds;
	t_vars	var;

	var.start = 0;
	var.quote_char = 0;
	var.h = 0;
	var.j = -1;
	var.x = 0;
	*tmp = malloc(sizeof(t_cmds) * pipe->cmd_len);
	cmds = *tmp;
	cmds->cmd_len = pipe->cmd_len;
	cmds->red_len = 0;
	while (++var.j < pipe->cmd_len)
	{
		cmds[var.j].red_len = num_of_redirects(pipe->cmds[var.j]);
		if (cmds[var.j].red_len)
			cmds[var.j].outs = malloc(sizeof(t_redirect) * cmds[var.j].red_len);
		utils_saving(pipe, cmds, &var);
		cmds[var.j].cmd = ft_split(pipe->cmds[var.j], ' ');
		var.h = 0;
		while (cmds[var.j].cmd[var.h])
			clean_quotes(cmds[var.j].cmd[var.h++]);
		var.h = 0;
	}
}
