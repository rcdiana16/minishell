/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:46:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/02 16:25:10 by cosmos           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
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
	int		c_pipe;
	int		c_red_i;
	int		c_red_o;
	int		here_doc;
	int		c_append;
}	t_command;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

//path/path.c
char		**get_path(void);
char		**split_path(char *path);
//path/find_ex_path.c
char		**add_slash(char **path_splited);
char		*find_no_builtin(char **good_path, char **command);
//builtins/cd.c
int			is_valid_path(char *path, t_env *env_mini);
//builtins/echo.c
void		ft_our_echo(char **cmd);
//builtins/env.c
void		ft_our_env(t_env *env_mini);
//builtins/pwd.c
char		*get_env_value(t_env *env, const char *var);

void		update_env(t_env *env, char *new_path, \
			char *env_to_update, int flag);
//builtins/util_pwd.c
void		ft_our_pwd(t_env *env);
char		*ft_find_dir(char *path);
char		*ft_find_gd_dir(char *path);
//builtins/util2_pwd.c
void		update_env_last_dir(t_env *env, char *new_path);
void		update_env_concat(t_env *env, char *current_pwd, char *new_path);
void		update_env_direct(t_env *env, char *new_path, int flag);
//free/free.c
void		free_command(t_command *cmd_info);
void		free_arr(char **tok);
void		free_node(t_env *head);
void		free_env_list(t_env *env);
//ft_list/list.c
t_env		*get_list_env(char **envp, t_env	*env_list);
//input/get_input.c
t_command	*get_input(void);
//split/split_bis.c
char		**ft_split2(const char *s, const char *delimiters);
//utils_split.c
bool		is_delimiter(char c, const char *delimiters);
void		initialize_vars(int *j, int *s_word);
int			get_end(const char *s, size_t i, const char *delimiters);
void		free_array(char **strs, int count);
char		*create_word(const char *str, int start, int end);
//utils2_split.c
char		**allocate_array(int word_count);
void		add_word_to_result(char **res, int j, char *word);
//check_cmd/check_builtins.c
int			check_builtins(char **cmd, t_env *env_mini);
//utils/utils.c
char		*get_env_value(t_env *env_mini, const char *var);

#endif
/*
,740 bytes in 88 blocks are still reachable in loss record 57 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x402A57: ft_strdup (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x401D07: create_node (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x401D73: append_node (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x401E7F: get_list_env (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400C43: initialize_environment (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400DE3: main (in /home/cosmos/42/minishell/minishell)

160 bytes in 90 blocks are still reachable in loss record 54 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x401CB3: create_node (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x401D73: append_node (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x401E7F: get_list_env (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400C43: initialize_environment (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400DE3: main (in /home/cosmos/42/minishell/minishell)

ytes in 8 blocks are still reachable in loss record 33 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x402B3B: ft_strjoin (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x4017BF: allocate_paths_with_slash (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x40189B: add_slash (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400BD3: handle_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400DD7: main (in /home/cosmos/42/minishell/minishell)

02 bytes in 8 blocks are still reachable in loss record 32 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x402DBF: fill_word (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x402C77: ft_split (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400E77: split_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400E57: get_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400B7F: handle_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400DD7: main (in /home/cosmos/42/minishell/minishell)

2 bytes in 1 blocks are still reachable in loss record 27 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x40176B: allocate_paths_with_slash (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x40189B: add_slash (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400BD3: handle_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400DD7: main (in /home/cosmos/42/minishell/minishell)

2 bytes in 1 blocks are still reachable in loss record 26 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x4030AF: ft_calloc (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x402BBF: ft_split (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400E77: split_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400E57: get_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400B7F: handle_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400DD7: main (in /home/cosmos/42/minishell/minishell)

0 bytes in 1 blocks are still reachable in loss record 20 of 87
==33558==    at 0x48854F0: malloc (vg_replace_malloc.c:446)
==33558==    by 0x402B3B: ft_strjoin (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x40229B: update_env_concat (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x402203: update_env (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x4024F3: update_pwd_env (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x402557: is_valid_path (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x401B17: check_builtins (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400C77: execute_command (in /home/cosmos/42/minishell/minishell)
==33558==    by 0x400E0B: main (in /home/cosmos/42/minishell/minishell)*/