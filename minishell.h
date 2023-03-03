/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:51:56 by mradwan           #+#    #+#             */
/*   Updated: 2023/03/03 15:24:21 by abdamoha         ###   ########.fr       */
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

typedef struct s_env
{
	char	**path;
	char	*user;
	char	*home;
}	t_env;

typedef struct s_vars
{
	int i;
    int j;
    int space_found;
    int quote_char;
	int x;
	int start;
	int xy;
	int in_d_quotes;
	int	in_quotes;
}	t_vars;

enum e_types
{
	IN_FILE,
	OUT_FILE,
	APPEND_OUT,
	APPEND_IN,
};

typedef struct s_redirect
{
	int		flag;
	char	*file_name;
}	t_redirect;

//< pwd ls < lsss < out > outfile -la | pwd cat | grep -n hello | cat -e

typedef struct s_cmds
{
	int			red_len;// = 4
	int			cmd_len;
	char		**cmd;// [0]-ls.. [1] -la
	t_redirect  *outs;
}	t_cmds;

typedef struct t_pipe
{
	int			cmd_len;
	int			env_count;
	char		**cmds;
	char		**m_env;
	char		**m_path;
	char		**tmp_env;
	t_list		*m_export;
	char		**tmp;
	char		***args; // {CMD1={CMD=ls, ARGS:ls, -l},CMD2={echo, h} }
	int			i;
	int			num_of_pipes;
	int			*ibq;
	t_env		*env;
}	t_pipe;

/***************      parse_tool          ****************/
int		is_space(char *str);
char	*ft_add_spaces(char *str);
void 	replace_spaces_tabs(char *str);

/***************      pipes_parse         ****************/
int	check_pipes(t_pipe *pipe, char *line, t_cmds *cmds);

/***************    redirection_parse     ****************/
int		check_redirect(t_pipe *cmd);
int		num_of_redirects(char *str);
void	remove_substr(char *s, unsigned int start, size_t len);

/***************      free_functions      ****************/
void	free_strings(char **av);
void	free_3d(char ***av);
void	free_all(t_pipe *pipe, t_cmds *cmd);

/***************      quotes_parse        ****************/
void	clean_quotes(char *str);
void	files_saving(t_pipe *pipe, t_cmds **tmp);

/***************      exec_part       ****************/

void	ms_exec(t_cmds *p, t_pipe *c);
void	ft_echo(t_cmds *p, int x, int y);
void	ft_pwd(t_cmds *p);
void	ft_env(t_cmds *p, t_pipe *c);
void	get_env(t_pipe *p, char **envp);
void	ft_cd(t_cmds *p, int x, int y);
void	ft_export(t_pipe *c, t_cmds *p, int i, int j);
void	ft_unset(t_cmds *p, int i, int j, t_pipe *c);
int		strncmp_orginal(const char *s1, const char *s2, unsigned int n);
int		found_first(char **m_env, int k, t_pipe *p);
void	fill_export_list(t_pipe *p);
void	fill_tmp_env(t_pipe *p);
void	check_builtin(t_cmds *p, t_pipe *c);
int		check_for_redirction(t_pipe *p);
int		count_cmds(char ***str);
void	check_other(t_pipe *p);
void	normal_exec(t_pipe *p);
char	**check_env_for_path(char **env);
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

#endif