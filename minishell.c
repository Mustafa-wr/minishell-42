/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/27 21:08:42 by mradwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipe;
	t_cmds	*cmds;
	char	*read;

	(void)av;
	(void)ac;
	cmds = NULL;
	get_env(&pipe, envp);
	fill_export(&pipe);
	g_exit_code = 0;
	main_init(&pipe);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		read = readline("\x1B[31mbash-3.3$\e[0m ");
		if (!read)
			return (free_and_exit_2(&pipe, cmds), printf("exit\n"), 0);
		if (ms_main_helper(&pipe, cmds, read))
			continue ;
		files_saving(&pipe, &cmds);
		main_helper(&pipe, cmds);
		add_history(read);
	}
}