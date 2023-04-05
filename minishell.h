/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/04 22:41:11 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>

extern int	g_exit_code;

typedef struct s_env
{
	char	**path;
	char	*user;
	char	*home;
}	t_env;

typedef struct s_vars
{
	int		i;
	int		j;
	int		h;
	int		empty;
	int		space_found;
	int		quote_char;
	int		x;
	int		start;
	int		len;
	int		xy;
	int		in_d_quotes;
	int		in_quotes;
	int		pid;
	char	*cmd_exec;
}	t_vars;

enum e_types
{
	IN_FILE,
	OUT_FILE,
	APPEND,
	HERE_DOC,
};

typedef struct s_redirect
{
	int		flag;
	char	*file_name;
}	t_redirect;

typedef struct s_cmds
{
	int			red_len;
	int			cmd_len;
	char		**cmd;
	t_redirect	*outs;
}	t_cmds;

typedef struct t_pipe
{
	int			cmd_len;
	int			env_count;
	char		**cmds;
	t_list		*m_env;
	char		**m_path;
	char		**tmp_env;
	t_list		*m_export;
	char		**tmp;
	int			i;
	int			k;
	int			j;
	int			b;
	int			ch;
	int			pid;
	int			fd[2][2];
	int			fd1;
	int			fd2;
	char		tmpfile[11];
	int			heredoc_len;
	char		*cmd_exec;
	int			t;
	t_list		*tmpp;
	t_list		*tmp2;
	t_list		*tmp3;
	int			fdin;
	int			fdout;
	int			cr;
}	t_pipe;

/***************      parse_tool          ****************/
char	*my_getenv(const char *name, t_pipe *pipe);
int		is_space(char *str);
char	*ft_add_spaces(char *str);
void	replace_spaces_tabs(char *str);

/***************      pipes_parse         ****************/
int		check_pipes(t_pipe *pipe, char *line, t_cmds *cmds);
void	dollar_expansion(char **str, t_pipe *pipe);

/***************    redirection_parse     ****************/
int		check_redirect(char *str);
int		num_of_redirects(char *str);
void	remove_substr(char *s, unsigned int start, size_t len);

/***************      free_functions      ****************/
void	free_strings(char **av);
void	free_all(t_pipe *pipe, t_cmds *cmd);

/***************      quotes_parse        ****************/
void	clean_quotes(char *str);
void	files_saving(t_pipe *pipe, t_cmds **tmp);

/***************      exec_part       ****************/

void	ms_exec(t_cmds *p, t_pipe *c);
void	ft_echo(t_cmds *p, int x, int y, t_pipe *c);
void	ft_pwd(t_cmds *p, t_pipe *c, int fd);
void	ft_env(t_cmds *p, t_pipe *c, int fd);
void	get_env(t_pipe *p, char **envp);
void	ft_cd(t_cmds *p, int x, int y, t_pipe *c);
void	ft_export(t_pipe *c, t_cmds *p, int i, int fd);
void	ft_unset(t_cmds *p, int i, int fd, t_pipe *c);
int		strncmp_orginal(const char *s1, const char *s2, unsigned int n);
int		found_first(char **m_env, int k, t_pipe *p);
void	fill_export_list(t_pipe *p);
void	fill_tmp_env(t_pipe *c);
int		check_builtin(t_cmds *p, t_pipe *c);
int		check_for_redirction(t_cmds *p, t_pipe *c);
int		count_cmds(char ***str);
void	check_other(t_cmds *p, t_pipe *c);
void	normal_exec(t_cmds *p, t_pipe *c);
char	**check_env_for_path(t_list *env);
char	*check_command_existence(char *av, char **path);
char	*check_with_access(char **path, char *str);
char	*backslash_case(char *av, int i);
void	last_sorting(t_pipe *p);
void	ms_redirection(t_pipe *p);
int		is_space(char *str);
int		cmd_index(t_pipe *p);
int		check_and_create(t_pipe *p, int i);
void	fill_export(t_pipe *c);
void	add_to_export(t_cmds *p, t_pipe *c, int i, int j);
void	insert_the_node(t_cmds *p, t_pipe *c);
int		check_if_exist(t_cmds *p, int i, int j, t_pipe *c);
int		len_till_equal(char *str);
int		check_for_equal(t_cmds *p, int i, int j);
void	changing_the_value(t_cmds *p, int i, int j, t_pipe *c);
int		check_for_flag(char *str);
char	*env_index(int index, t_list *tmp);
void	changing_the_env_v(t_cmds *p, int i, int j, t_pipe *c);
void	free_list(t_list **lst);
void	free_and_exit(t_pipe *c, t_cmds *p);
void	unset_cmp(t_cmds *p, t_list *lst, int i, int j);
void	multiple_pipes(t_cmds *p, t_pipe *c);
void	closing_fds(t_pipe *c);
void	update_env(t_pipe *c);
int		check_executable(t_pipe *c, t_cmds *p);
int		increase_shlvl_value(char *str);
void	change_shlv(t_cmds *p, t_pipe *c, t_list *lst);
void	get_path(char **str, t_pipe *c);
int		check_exec_redirect(t_cmds *p, t_pipe *c, int pm, int j);
void	free_and_exit_2(t_pipe *c, t_cmds *p);
void	write_in_fd(t_cmds *p, int x, int y, t_pipe *c);
int		check_input_redirect(t_cmds *p, t_pipe *c, int pm, int j);
int		check_heredoc(t_cmds *p, t_pipe *c);
int		exec_heredoc(t_cmds *p, t_pipe *c, int i);
void	heredoc_len(t_pipe *c, t_cmds *p);
int		heredoc_redierction(t_cmds *p, t_pipe *c, char *s);
int		check_to_add(t_pipe *c, t_cmds *p, int i, int j);
void	input_red(t_cmds *p, t_pipe *c);
void	output_red(t_cmds *p, t_pipe *c, char *cmd);
void	echo_new_line(t_cmds *p, int x, int y, t_pipe *c);
void	echo_flag(t_cmds *p, int x, int y, t_pipe *c);
int		heredoc_condition(int fd);
void	sec_cmd(t_pipe *c, int i, int j);
void	close_first_pipe(t_cmds *p, t_pipe *c);
void	close_second_pipe(t_pipe *c);
void	third_cmd(t_cmds *p, t_pipe *c, int j);
void	ft_exit(t_pipe *c, t_cmds *p);
int		builtins_pipes(t_cmds *p, t_pipe *c, int fd, int j);
void	update_pwd(t_pipe *c, char *str, char *p, int k);
void	update_export(t_pipe *c, char *str, char *p, int k);
int		input_check(t_cmds *p, t_pipe *c, int j);
int		output_check(t_cmds *p, t_pipe *c);
void	exit_once(t_cmds *p, t_pipe *c);
void	ft_echo_p(t_cmds *p, int x, int pm, t_pipe *c);
void	ft_unset_p(t_cmds *p, int i, int fd, t_pipe *c);
void	ft_export_p(t_pipe *c, t_cmds *p, int i, int fd);
void	ft_cd_p(t_cmds *p, int x, int pm, t_pipe *c);
void	ft_pwd_p(t_cmds *p, t_pipe *c, int pm);
void	ft_env_p(t_cmds *p, t_pipe *c, int pm);
#endif