/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:40:11 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/06 17:40:15 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_sigint_handler(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_code = 130;
	(void)sig;
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
	}
}

int	get_sig_status(int sig_no)
{
	if (sig_no == SIGINT)
		;
	else if (sig_no == SIGQUIT)
		printf("Quit\n");
	return (128 + sig_no);
}

void	hdoc_sigint_handler(int sig)
{
	int	is_parent_proc;

	is_parent_proc = (waitpid(-1, NULL, WNOHANG) == -1);
	if (is_parent_proc)
	{
		close(0);
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	(void)sig;
}
