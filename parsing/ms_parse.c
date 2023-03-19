/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/19 20:28:11 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_code = 0;

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
	if (!check_redirect(read))
	{
		printf("syntax error near unexpected token \n");
		add_history(read);
		g_exit_code = 258;
		return (1);
	}
	else if (!check_pipes(pipe, read, cmds))
	{
		printf("Error\n");
		add_history(read);
		g_exit_code = 258;
		return (1);
	}
	return (0);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipe;
	t_cmds	*cmds;
	char	*read;

	(void)av;
	if (ac != 1)
		return (0);
	get_env(&pipe, envp);
	fill_export(&pipe);
	pipe.m_path = NULL;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		read = readline("minishell$ ");
		if (!read)
			return (free_list(&pipe.m_env), printf("exit\n"), 0);
		if (ms_main_helper(&pipe, cmds, read))
			continue ;
		files_saving(&pipe, &cmds);
		ms_exec(cmds, &pipe);
		// free_all(&pipe, cmds);
		add_history(read);
	}
}

// int main(int ac, char **av, char **envp)
// {
// 	// t_env	path;
// 	t_pipe	pipe;
// 	t_cmds	*cmds;
// 	char	*read;

// 	(void)av;
// 	(void)envp;
// 	if (ac != 1)
// 		return (0);
// 	// printf("env[0] = %s\n", envp[2]);
// 	get_env(&pipe, envp);
// 	fill_export(&pipe);
// 	while (1)
// 	{
// 		// enviroments(envp, &path);
// 		read = readline("minishell$ ");
// 		if (!read)
// 			return (0);
// 		if (is_space(read))
// 			continue ;
// 		// 	printf("%s\n", read);
// 		// if(!check_string(read))
// 		// 	printf("syntax error multiple line not allowed\n");
// 		if (!check_pipes(&pipe, read, cmds))
// 		{
// 			printf("Error\n");
// 			// free_strings(path.path);
// 			// return(0);
// 			add_history(read);
// 			continue ;
// 		}
// 		else if (!check_redirect(read))
// 		{
// 			printf("syntax error near unexpected token \n");
// 			// free_strings(path.path);
// 			// return (0);
// 			add_history(read);
// 			continue ;
// 		}
// 		files_saving(&pipe, &cmds);
// 		ms_exec(cmds, &pipe);
// 		// printf("val: %d\n", cmds.red_len);
// 		// free_and_exit(&pipe, cmds);
// 		add_history(read);
// 	}
// }