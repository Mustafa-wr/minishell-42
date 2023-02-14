/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/14 17:59:31 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	free_strings(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

// int	get_tokens(char **p_start, char *es, char **q, char **eq)
// {
	
// }

// int	syntax(char *s)
// {
// 	return(c == '>' || c == '<' || (c == '>' && c == '>') || (c == '<' && cmd-c == '<'));
// }

int check_string(char *str)
{
    int i = 0;
    // char **split;
	int in_single_quote = 0;
	int in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (in_single_quote)
				in_single_quote = 0;
			else if (!in_double_quote)
				in_single_quote = 1;
		}
		else if (str[i] == '\"')
		{
			if (in_double_quote)
				in_double_quote = 0;
			else if (!in_single_quote)
				in_double_quote = 1;
		}
		else if (str[i] == '\\')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (!str[i])
				return (0);
		}
		i++;
	}
	if (in_single_quote || in_double_quote)
		return (0);
    return (1);
}

void parse_cd_command(char *input)
{
  char **token;
  token = ft_split(input, ' ');
  if(!token || token[0] == NULL)
	return;
  if (strcmp(token[0], "cd") != 0 || strcmp(token[0], "ls") != 0) {
    printf("Error: Not a valid command\n");
    return ;
  }
  token = ft_split(NULL, ' ');
  if (token == NULL) {
    printf("Error: Missing argument\n");
    return ;
  }
}

// void sigintHandler(int sig_num)
// {
// 	if(sig_num == SIGINT)

// }

void	enviroments(char **envp, t_env *d_env)
{
	int i = 0;
	char *string;

	while (ft_strncmp(envp[i], "PATH=", 5) != 0 && envp[i])
		i++;
	string = ft_strchr(envp[i], '/');
	d_env->path = ft_split(string, ':');
	i = 0;
	// while (envp[i][0] != 'U')
	// 	i++;
	// string = ft_strchr(envp[i], '=');
	// string++;
	// d_env->user = string;
	// i = 0;
	// while (envp[i][0] != 'H')
	// 	i++;
	// string = ft_strchr(envp[i], '/');
	// d_env->home = string;
	// i = 0;
	// while (d_path->path[i])
	// {
	// 	printf("%s\n", d_path->path[i]);
	// 	i++;
	// }
}

void	clean_quotes(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if(str[i] != '\'' && str[i] != '"')
			str[j++] = str[i];
		++i;
	}
	str[j] = '\0';
}

int check_pipes(t_pipe *pipe, char *line)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	quotes = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (quotes == 0)
				quotes = line[i];
			else
				quotes = 0;
			i++;
			continue ;
		}
		if (line[i] == '|' && !quotes)
		{
			j = i + 1;
			while (line[j] == ' ')
				j++;
			if (line[j] == '\0' || line[j] == '|')
				return (0);
		}
		i++;
	}
	if (!check_string(line))
		return (0);
	pipe->cmds = ft_split(line, '|');
	return (1);
}

int	check_redirect(t_pipe *cmd)
{
	int	i;
	int	j;
	int	in_quotes;
	int	in_d_quotes;

	i = 0;
	j = 0;
	in_d_quotes = 0;
	in_quotes = 0;
	while (cmd->cmds[j])
	{
		i = 0;
		while (cmd->cmds[j][i])
		{
			if (cmd->cmds[j][i] == '\'')
			{
				if (!in_quotes)
					in_quotes = 1;
				else
					in_quotes = 0;
			}
			if (cmd->cmds[j][i] == '\"')
			{
				if (!in_d_quotes)
					in_d_quotes = 1;
				else
					in_d_quotes = 0;
			}
			if (cmd->cmds[j][i] == '>' || cmd->cmds[j][i] == '<' || \
				(cmd->cmds[j][i] == '>' && cmd->cmds[j][i + 1] == '>') \
					|| (cmd->cmds[j][i] == '<' && cmd->cmds[j][i + 1] == '<'))
			{
				i++;
				if ((cmd->cmds[j][i] == '<' && cmd->cmds[j][i - 1] == '<') \
					|| (cmd->cmds[j][i] == '>' && cmd->cmds[j][i - 1] == '>'))
					i++;
				while (cmd->cmds[j][i] == ' ')
					i++;
				if ((cmd->cmds[j][i] == '>' || cmd->cmds[j][i] == '<') \
					&& (!in_quotes && !in_d_quotes))
					return (0);
				while (cmd->cmds[j][i] == ' ')
					i++;
				if (cmd->cmds[j][i] == '\0')
				{
					free_strings(cmd->cmds);
					// free_strings(cmd->env->path);
					return (0);
				}
			}
			i++;
		}
		j++;
	}
		i = 0;
	while (cmd->cmds[i])
		clean_quotes(cmd->cmds[i++]);
	i = 0;
	while (cmd->cmds[i])
		printf("%s\n", cmd->cmds[i++]);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_env path;
	t_pipe	pipe;
	char *read;
	if (ac != 1)
		return (0);
	
	// printf("env[0] = %s\n", envp[2]);
	while(1)
	{
		enviroments(envp, &path);
		read = readline("minishell$ ");
		if(!read)
			return(0);
		// if (is_space(read) == 0)
		// 	printf("%s\n", read);
		// if(!check_string(read))
		// 	printf("syntax error multiple line not allowed\n");
		if(!check_pipes(&pipe, read))
		{
			printf("Error\n");
			free_strings(path.path);
			// return(0);
		}
		else if(!check_redirect(&pipe))
		{
			printf("syntax error\n");
			free_strings(path.path);
			// return (0);
		}
		add_history(read);
	}
}
