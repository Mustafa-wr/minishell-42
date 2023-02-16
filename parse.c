/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/16 18:00:05 by mradwan          ###   ########.fr       */
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

int	check_string(char *str)
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

void clean_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	j = 0;
	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == '\0')
				quote = str[i];
			else if (quote == str[i])
				quote = '\0';
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	pipe_helper(char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	if (line[len] == '|')
		return (0);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (0);
	return (1);
}

int	check_pipe_in_quotes(char *line, int i, int quotes, int j)
{
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
	return (1);
}

int check_pipes(t_pipe *pipe, char *line)
{
	int	i;
	int	j;
	int	quotes;

	quotes = 0;
	i = 0;
	j = 0;
	if (!pipe_helper(line))
		return (0);
	if (!check_pipe_in_quotes(line, i, quotes, j))
		return (0);
	if (!check_string(line))
		return (0);
	pipe->cmds = ft_split(line, '|');
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
