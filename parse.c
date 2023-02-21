/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/21 20:39:49 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
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

void	for_less_than(char *str, int j, int i, char *new_str)
{
	if (str[i] == '<' && str[i + 1] != '<')
	{
		new_str[j++] = ' ';
		new_str[j++] = '<';
		new_str[j++] = ' ';
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		i++;
		new_str[j++] = ' ';
		new_str[j++] = '<';
		new_str[j++] = '<';
		new_str[j++] = ' ';
	}
}

char *ft_add_spaces(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		single_q;
	int		double_q;

	i = 0;
	j = 0;
	single_q = 0;
	double_q = 0;
	new_str = malloc(ft_strlen(str) * 3);
	while (str[i])
	{
		if (str[i] == '\'' && double_q == 0)
			single_q = !single_q;
		else if (str[i] == '\"' && single_q == 0)
			double_q = !double_q;
		if (!single_q && !double_q)
		{
			// if (str[i] == '<' && str[i + 1] != '<')
			// {
			// 	new_str[j++] = ' ';
			// 	new_str[j++] = '<';
			// 	new_str[j++] = ' ';
			// }
			// else if (str[i] == '<' && str[i + 1] == '<')
			// {
			// 	i++;
			// 	new_str[j++] = ' ';
			// 	new_str[j++] = '<';
			// 	new_str[j++] = '<';
			// 	new_str[j++] = ' ';
			// }
			for_less_than(str, j, i, new_str);
			if (str[i] == '>' && str[i + 1] != '>')
			{
				new_str[j++] = ' ';
				new_str[j++] = '>';
				new_str[j++] = ' ';
			}
			else if (str[i] == '>' && str[i + 1] == '>')
			{
				i++;
				new_str[j++] = ' ';
				new_str[j++] = '>';
				new_str[j++] = '>';
				new_str[j++] = ' ';
			}
			else
				new_str[j++] = str[i];
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

// char	*ft_add_spaces(char *str)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new_str = malloc(ft_strlen(str) * 3);
// 	while (str[i])
// 	{
// 		if (str[i] == '<' && str[i + 1] != '<')
// 		{
// 			new_str[j++] = ' ';
// 			new_str[j++] = '<';
// 			new_str[j++] = ' ';
// 		}
// 		else if (str[i] == '<' && str[i + 1] == '<')
// 		{
// 			i++;
// 			new_str[j++] = ' ';
// 			new_str[j++] = '<';
// 			new_str[j++] = '<';
// 			new_str[j++] = ' ';
// 		}
// 		else if (str[i] == '>' && str[i + 1] != '>')
// 		{
// 			new_str[j++] = ' ';
// 			new_str[j++] = '>';
// 			new_str[j++] = ' ';
// 		}
// 		else if (str[i] == '>' && str[i + 1] == '>')
// 		{
// 			i++;
// 			new_str[j++] = ' ';
// 			new_str[j++] = '>';
// 			new_str[j++] = '>';
// 			new_str[j++] = ' ';
// 		}
// 		else
// 			new_str[j++] = str[i];
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	free(str);
// 	return (new_str);
// }

// void	skip_spaces(char *str)
// {
// 	int	i;
// 	int	j;
// 	int	quote;

// 	j = 0;
// 	i = 0;
// 	quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ')
// 			str[j++] = str[i];
// 		else
// 			str[j++] = str[i];
// 		i++;
// 	}
// 	str[j] = '\0';
// }

void	clean_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	j = 0;
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int main(int ac, char **av, char **envp)
{
	// t_env	path;
	t_pipe	pipe;
	char	*read;

	(void)av;
	(void)envp;
	if (ac != 1)
		return (0);
	// printf("env[0] = %s\n", envp[2]);
	while (1)
	{
		// enviroments(envp, &path);
		read = readline("minishell$ ");
		if (!read)
			return (0);
		// if (is_space(read) == 0)
		// 	printf("%s\n", read);
		// if(!check_string(read))
		// 	printf("syntax error multiple line not allowed\n");
		if (!check_pipes(&pipe, read))
		{
			printf("Error\n");
			// free_strings(path.path);
			// return(0);
		}
		else if (!check_redirect(&pipe))
		{
			printf("syntax error\n");
			// free_strings(path.path);
			// return (0);
		}
		// free_3d(pipe.args);
		add_history(read);
	}
}
