/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 21:20:22 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_code = 0;

int	init_shell(char **env, t_env **env_list, char ***path_splitted, \
	char ***path_sp_w_slash)
{
	*path_splitted = NULL;
	*path_sp_w_slash = NULL;
	*env_list = initialize_environment(env, *env_list);
	if (!*env_list)
		return (1);
	disable_echoctl();
	return (0);
}

int	handle_user_input(t_command **cmd_info, t_env *env_list, \
	char ***path_splitted, char ***path_sp_w_slash)
{
	int	input_status;

	input_status = 0;
	set_signals();
	handle_path(path_splitted, path_sp_w_slash, env_list);
	if (isatty(STDIN_FILENO))
	{
		input_status = handle_input(cmd_info, env_list, 0);
		if (input_status == -1)
		{
			return (-1);
		}
		if (input_status == 1)
			return (0);
	}
	else
	{
		if (handle_input(cmd_info, env_list, 1))
			return (0);
	}
	return (1);
}

void	execute_shell_loop(t_env *env_list, char **env)
{
	char		**path_splitted;
	char		**path_sp_w_slash;
	t_command	*cmd_info;
	int			input_status;

	if (init_shell(env, &env_list, &path_splitted, &path_sp_w_slash) == 1)
		return ;
	while (1)
	{
		input_status = handle_user_input(&cmd_info, env_list, \
		&path_splitted, &path_sp_w_slash);
		if (input_status == -1)
		{
			free_all(cmd_info, path_sp_w_slash, env_list);
			exit(0);
		}
		if (input_status == 0)
			continue ;
		signal(SIGINT, SIG_IGN);
		execute_command(cmd_info, path_sp_w_slash, env_list);
		set_signals();
		if (cmd_info)
			free_command(cmd_info);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;

	if (ac == 0)
		return (1);
	*av = NULL;
	env_list = NULL;
	execute_shell_loop(env_list, env);
	return (0);
}
