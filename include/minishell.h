/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:46:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/15 11:53:54 by maximemarti      ###   ########.fr       */
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

extern int	g_code;

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
	int		c_pipe;
	int		c_red_i;
	int		c_red_o;
	int		here_doc;
	int		c_append;
	int		flag;
	int		quotes_s;
	int		quotes_d;
}	t_command;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd_state
{
	char	*cmd;
	int		i;
}	t_cmd_state;

//----------------------------builtins---------------------------------
//----cd_utils.c----
void		update_env(t_env *env, char *new_path, \
			char *env_to_update, int flag);
//----cd.c---
int			is_valid_path(char *path, t_env *env_mini);
//----echo.c----
void		ft_our_echo(char **cmd);
//----env.c----
void		ft_our_env(t_env *env_mini);
//----exit.c----
void		ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, \
			char **path);
//----export.c----
void		ft_export(t_env *env_mini, char **cmd);
//----export_utils.c----
void		init_new_variable(t_env **new_var, char **tokens);
//----pwd.c----
void		ft_our_pwd(t_env *env_mini);
//----unset.c----
void		ft_unset(t_env *env_mini, char **cmd);
//----------------------------check_cmd----------------------------
//----check_builtins.c----
int			check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
			char **path);
//----------------------------execute----------------------------
//----execute.c----
int			execute_command(t_command *cmd_info, char **path_sp_w_slash, \
			t_env *env_list);
//----execute_utils.c----
char		*find_no_builtin(char **good_path, char **command);
//----execute_utils_env.c
char		**convert_env_to_array(t_env *env_mini);
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
t_command	*get_input(t_env *env_mini, int mode);
t_command	*make_good_cmd2(t_command *cmd_info);
t_command	*make_good_cmd(t_command *cmd_info);
void		count_redirections(char *cmd, t_command *cmd_info, int *i);
//----handle_input.c----
int			handle_input(t_command **cmd_info, t_env *env_mini, int mode);
//----rep_env_vars.c----
char		*replace_env_vars(char *cmd, t_env *env_mini);
//----utils_input.c----
void		clean_quotes(char *token);
void		remove_single_quotes(char *token);
t_command	*initialize_command(void);
void		count_special_chars(char *cmd, t_command *cmd_info);
void		process_tokens(t_command *cmd_info, t_env *env_mini);
//----quote.c----
int			has_enclosed_single_quotes(t_command *cmd_info);
void		delete_quotes(char *token);
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
//----------------------------split----------------------------
//----split_bis.c
char		**ft_split2(const char *s, const char *delimiters);
//----utils_split.c----
char		*create_word(const char *str, int start, int end);
int			get_end(const char *s, size_t i, const char *delimiters);
void		initialize_vars(int *j, int *s_word);
bool		is_delimiter(char c, const char *delimiters);
void		free_array(char **strs, int count);
//---utils2_split.c
void		add_word_to_result(char **res, int j, char *word);
char		**allocate_array(int word_count);
//----------------------------utils----------------------------
//----utils.c----
char		*get_env_value(t_env *env_mini, const char *var);
int			process_exit_code(char *result, int j);
void		set_gcode(int val);

#endif
