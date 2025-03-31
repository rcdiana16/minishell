/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:46:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 12:45:14 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_split_data
{
	char		**res;
	int			*j;
	int			*s_word;
	const char	*delimiters;
	const char	*s;
}	t_split_data;

typedef struct s_command
{
	char	**tokens;
	char	*file_out;
	char	*file_in;
	int		fd_out;
	int		fd_in;
	int		c_pipe;
	int		c_red_i;
	int		c_red_o;
	int		here_doc;
	int		fd_here_doc;
	int		c_append;
	int		flag;
	int		quotes_s;
	int		quotes_d;
	int		exit_code;
}	t_command;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd_state
{
	char		*cmd;
	int			i;
	t_command	*cmd_info;
}	t_cmd_state;

typedef struct s_shell
{
	int	exit_code;
}	t_shell;

typedef struct s_shell_env
{
	t_env	*env_mini;
	t_shell	*shell;
}	t_shell_env;

typedef struct s_shell_data
{
	char	**path_splitted;
	char	**path_sp_w_slash;
	t_shell	shell;
	int		original_stdout;
	int		original_stdin;
}	t_shell_data;
typedef struct s_pipe_exec_info
{
	int			prev_pipe_fd;
	int			pipe_fd[2];
	int			fd_redir_out;
	int			i;
	char		**current_command;
	char		**path_sp_w_slash;
	t_env		*env_list;
	t_command	*cmd_info;
}	t_pipe_exec_info;
//----------------------------builtins---------------------------------
//----cd_utils.c----
void		update_env(t_env *env, char *new_path, \
			char *env_to_update, int flag);
//----cd.c---
int			is_valid_path(char *path, t_env *env_mini, \
			t_command *cmd_info, char **cmd);
//----echo.c----
void		ft_our_echo(char **cmd);
//----env.c----
int			ft_our_env(t_env *env_mini, char **cmd);
//----exit.c----
void		ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, \
			char **path);
//----export.c----
int			ft_export(t_env *env_mini, char **cmd);
void		join_quoted_values(char **cmd, char **value);
void		assign_value(char **cmd, char **value);
//----export_utils.c----
void		init_new_variable(t_env *new_var, char **tokens);
int			is_valid_variable_name(char *name);
char		**check_split(char **cmd);
char		**get_tokens(char *cmd);
void		join_cmd_values(char **cmd, char **value);
//----export_utils_update.c----
int			handle_existing_variable(t_env *env_mini, char **cmd);
int			update_existing_variable(t_env *env_mini, char **cmd);
//----export_utils_bis.c----
//----pwd.c----
void		ft_our_pwd(t_env *env_mini);
//----unset.c----
void		ft_unset(t_env *env_mini, char **cmd);
//----------------------------check_cmd----------------------------
//----check_builtins.c----
int			check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
			char **path);
void		add_new_variable(t_env *env_mini, char **tokens, t_env *new_var);
//----------------------------execute----------------------------
//----execute.c----
int			execute_command(t_command *cmd_info, char **path_sp_w_slash, \
			t_env *env_list);
int			open_file(char *file, int mode);
int			manage_redirection(t_command *cmd_info);
char		**check_redir(t_command *cmd_info);
int			execute_child_process(t_command *cmd_info, char **path_sp_w_slash, \
			t_env *env_list);
//----execute_utils.c----
char		*find_no_builtin(char **good_path, char **command);
//----execute_utils_env.c
char		**convert_env_to_array(t_env *env_mini);
//----execute_pipe.c----
char		**clean_redir(char **cmd_tokens, t_command *cmd_info);
int			execute_child_process_pipe(char **cmd_info, char **path_sp_w_slash, \
			t_env *env_list, t_command *stru);
char		*find_builtin_or_exit_pipe(char **path_sp_w_slash, char **cmd_inf, \
			t_env *env_list, t_command *stru);
//----execute_pipe_utils.c----
int			execute_pipes(t_command *cmd_info, \
			char **path_sp_w_slash, t_env *env_list);
int			child_process_execute_command(t_pipe_exec_info pipe_exec_info);
void		child_process_handle_redirection(t_pipe_exec_info pipe_exec_info);
//----utils_pipe.c----
int			get_pipe_bounds(t_command *cmd_info, int i, int *start, int *end);
char		**get_pipe_command(t_command *cmd_info, int i);
int			create_pipe(int *pipe_fd);
void		child_process_setup_io(t_pipe_exec_info pipe_exec_info);
int			execute_child_process_pipe_helper(t_pipe_exec_info pipe_exec_info);
//----utils.c----
void		exec_builtin_or_exit_pipe(char **command, t_command *cmd_info, \
			t_env *env_list, char **path_sp_w_slash);
//----check_redir.c----
int			open_file(char *file, int mode);
char		**check_redir(t_command *cmd_info);
int			manage_redirection(t_command *cmd_info);
void		execute_in_child(t_command *cmd_info, char **path_sp_w_slash, \
			t_env *env_list);
//----------------------------free----------------------------
//----free.c---
void		free_command(t_command *cmd_info);
void		free_node(t_env *node);
void		free_env_list(t_env *env);
void		free_split_data(t_split_data *data);
void		free_cmd_state(t_cmd_state *state);
//----free_bis.c----
void		free_all(t_command *cmd_info, char **path_sp_w_slash, \
			t_env *env_list);
void		free_arr(char **tok);
//----------------------------ft_list----------------------------
//----list.c----
t_env		*initialize_environment(char **env, t_env *env_list);
//----------------------------input----------------------------
//----get_input.c----
t_command	*get_input(t_env *env_mini, int mode, t_shell *shell, \
			char **path);
t_command	*verify_and_split_command(char *cmd, t_env *env_mini, \
			t_shell *shell);
//----get_input_utils.c----
char		**ft_strjoin_arr(char *first, char **arr);
char		**tokenize_quotes(char *input);
//----handle_input.c----
char		*make_good_cmd2(char *cmd);
char		*make_good_cmd(char *cmd);
void		remove_newline(char *str);
int			copy_non_var_part(t_cmd_state *state, char *result, int j);
//----rep_env_vars.c----
char		*replace_env_vars(char *cmd, t_env *env_mini, t_shell *shell);
int			process_env_var(t_cmd_state *state, char *result, \
			int j, t_env *env_mini);
//----rep_env_vars_utils.c----
int			process_var(t_cmd_state *state, char *result, \
			int j, t_shell_env *shell_env);
//----utils_input.c----
void		count_redirections(char *cmd, t_command *cmd_info);
t_command	*initialize_command(t_shell *shell);
void		count_special_chars(char *cmd, t_command *cmd_info);
void		process_tokens(t_command *cmd_info, t_env *env_mini, \
			t_shell *shell);
void		remove_newline(char *str);
//----quote.c----
bool		has_enclosed_single_quotes(char *token);
bool		has_enclosed_double_quotes(char *token);
void		delete_quotes(char *token);
void		clean_quotes(char *token);
void		remove_single_quotes(char *token);
//----redirection.c----
void		count_redirections(char *cmd, t_command *cmdf_info);
//----------------------------path----------------------------
//----path.c---
void		handle_path(char ***path_splitted, char ***path_sp_w_slash, \
			t_env *env_mini);
//---path_utils.c----
char		**add_slash(char **path_splited);
int			count_paths(char **path_splited);
//----------------------------signals----------------------------
//----ctrl_c.c----
void		disable_echoctl(void);
void		set_signals(void);
void		sigint(void);
void		handle_sigint(int sig);
//----ctrl_nothing.c----
void		sigquit(void);
void		handle_sigquit(int sig);
//----------------------------utils----------------------------
//----utils.c----
char		*get_env_value(t_env *env_mini, const char *var);
int			process_exit_code(char *result, int j, t_shell *shell);

#endif
