/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/09 14:11:31 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int is_space(char *str)
{
	int i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return(1);
	return(0);
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

int	syntax(char c)
{
	return(c == '|' || c == 39 || c == 34 || \
			c == '>' || c == '<');
}



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
				return 0;
		}
		i++;
	}
	if (in_single_quote || in_double_quote)
		return 0;
    return 1;
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

void	enviroments(char **envp, t_env *d_path)
{
	int i = 0;
	char *path;

	while (envp[i][0] != 'P')
		i++;
	path = ft_strchr(envp[i], '/');
	d_path->path = ft_split(path, ':');
	// i = 0;
	// while (d_path->path[i])
	// {
	// 	printf("%s\n", d_path->path[i]);
	// 	i++;
	// }
}

int	check_pipes(t_pipe *pipe, char *line)
{
	int	i;
	int j = 0;

	i = 0;
	while (line[i])
	{
		if(line[i] == '|')
			j++;
		i++;
	}
	i = 0;
	pipe->cmds = ft_split(line, '|');
	while (pipe->cmds[i])
		i++;
	printf("%d\n", i);
	printf("%d\n", j);
	if(i == j)
		return 0;
	return(1);
}

int main(int ac, char **av, char **envp)
{
	(void)av;
	t_env path;
	t_pipe	pipe;
	char *read;
	if (ac != 1)
		return(0);
	enviroments(envp, &path);
	// printf("env[0] = %s\n", envp[2]);
	while(1)
	{
		read = readline("minishell $");
		if(!read)
			return(0);
		if (is_space(read) == 0)
			printf("%s\n", read);
		if(!check_string(read))
			printf("syntax error multiple line not allowed\n");
		if(!check_pipes(&pipe, read))
			printf("Error\n");
		add_history(read);
	}
}
