/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/03 14:27:06 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ms_main_helper(t_pipe *pipe, t_cmds *cmds, char *read)
{
	if (is_space(read))
		return (1);
	if (!check_pipes(pipe, read, cmds))
	{
		printf("Error\n");
		add_history(read);
		return 1;
	}
	else if (!check_redirect(pipe))
	{
		printf("syntax error near unexpected token \n");
		// free_strings(path.path);
		// return (0);
		add_history(read);
		return 1;
	}
	return 0;
}

int main(int ac, char **av, char **envp)
{
	// t_env	path;
	t_pipe	pipe;
	t_cmds	*cmds;
	char	*read;

	(void)av;
	(void)envp;
	if (ac != 1)
		return (0);
	// printf("env[0] = %s\n", envp[2]);
	while (1)
	{
		read = readline("minishell$ ");
		if (!read)
			return (0);
		// if (is_space(read))
		// 	continue ;
		// if (!check_pipes(&pipe, read, cmds))
		// {
		// 	printf("Error\n");
		// 	add_history(read);
		// 	continue ;
		// }
		// else if (!check_redirect(&pipe))
		// {
		// 	printf("syntax error near unexpected token \n");
		// 	// free_strings(path.path);
		// 	// return (0);
		// 	add_history(read);
		// 	continue ;
		// }
		if (ms_main_helper(&pipe, cmds, read))
			continue ;
		files_saving(&pipe, &cmds);
		// printf("val: %d\n", cmds.red_len);
		// free_all(&pipe, cmds);
		add_history(read);
	}
}
