/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/27 19:51:11 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// static void	add_spaes(int *j, char **new_str, int var)
// {
// 	(*new_str)[(*j)++] = ' ';
// 	if (var == 0)
// 		(*new_str)[(*j)++] = '<';
// 	else if (var == 1)
// 	{
// 		(*new_str)[(*j)++] = '<';
// 		(*new_str)[(*j)++] = '<';
// 	}
// 	else if (var == 2)
// 		(*new_str)[(*j)++] = '>';
// 	else if (var == 3)
// 	{
// 		(*new_str)[(*j)++] = '>';
// 		(*new_str)[(*j)++] = '>';
// 	}
// 	(*new_str)[(*j)++] = ' ';
// }

// void	add_spaces_helper(char **str, int *i, int *j, char **new_str)
// {
// 	if ((*str)[*i] == '<' && (*str)[*i + 1] != '<')
// 		add_spaes(j, new_str, 0);
// 	else if ((*str)[*i] == '<' && (*str)[*i + 1] == '<')
// 	{
// 		(*i)++;
// 		add_spaes(j, new_str, 1);
// 	}
// 	else if ((*str)[*i] == '>' && (*str)[*i + 1] != '>')
// 		add_spaes(j, new_str, 2);
// 	else if ((*str)[*i] == '>' && (*str)[*i + 1] == '>')
// 	{
// 		(*i)++;
// 		add_spaes(j, new_str, 3);
// 	}
// 	else
// 		(*new_str)[(*j)++] = (*str)[(*i)];
// }

// char *ft_add_spaces(char *str)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;
// 	int		single_q;
// 	int		double_q;

// 	i = -1;
// 	j = 0;
// 	single_q = 0;
// 	double_q = 0;
// 	new_str = malloc(ft_strlen(str) * 3 + 2);
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'' && double_q == 0)
// 			single_q = !single_q;
// 		else if (str[i] == '\"' && single_q == 0)
// 			double_q = !double_q;
// 		if (!single_q && !double_q)
// 		{
// 			// if (str[i] == '<' && str[i + 1] != '<')
// 			// 	add_spaes(&j, &new_str, 0);
// 			// else if (str[i] == '<' && str[i + 1] == '<')
// 			// {
// 			// 	i++;
// 			// 	add_spaes(&j, &new_str, 1);
// 			// }
// 			// else if (str[i] == '>' && str[i + 1] != '>')
// 			// 	add_spaes(&j, &new_str, 2);
// 			// else if (str[i] == '>' && str[i + 1] == '>')
// 			// {
// 			// 	i++;
// 			// 	add_spaes(&j, &new_str, 3);
// 			// }
// 			// else
// 			// 	new_str[j++] = str[i];
// 			add_spaces_helper(&str, &i, &j, &new_str);
// 		}
// 		else
// 			new_str[j++] = str[i];
// 	}
// 	new_str[j] = '\0';
// 	free(str);
// 	return (new_str);
// }

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
	if (ac != 1)
		return (0);
	// printf("env[0] = %s\n", envp[2]);
	get_env(&pipe, envp);
	fill_export(&pipe);
	while (1)
	{
		// enviroments(envp, &path);
		read = readline("minishell$ ");
		if (!read)
			return (0);
		if (is_space(read))
			continue ;
		// 	printf("%s\n", read);
		// if(!check_string(read))
		// 	printf("syntax error multiple line not allowed\n");
		if (!check_pipes(&pipe, read))
		{
			printf("Error\n");
			continue;
			// free_strings(path.path);
			// return(0);
		}
		else if (!check_redirect(&pipe))
		{
			printf("syntax error near unexpected token \n");
			// free_strings(path.path);
			// return (0);
			continue;
		}
		ms_exec(&pipe);
		add_history(read);
	}
}