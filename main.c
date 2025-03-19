/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/19 13:32:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	init_shell(char **env, t_env **env_list, char ***path_splitted, \
	char ***path_sp_w_slash)
{
	*path_splitted = NULL;
	*path_sp_w_slash = NULL;
	*env_list = initialize_environment(env, *env_list);
	disable_echoctl();
	return (0);
}

int	handle_user_input(t_command **cmd_info, t_env *env_list, \
	t_shell *shell)
{
	set_signals();
	if (isatty(STDIN_FILENO))
	{
		*cmd_info = get_input(env_list, 0, shell);
		if (!*cmd_info)
			return (0);
	}
	else
	{
		*cmd_info = get_input(env_list, 1, shell);
		if (!*cmd_info)
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
	t_shell		shell;

	shell.exit_code = 0;
	if (init_shell(env, &env_list, &path_splitted, &path_sp_w_slash) == 1)
		return ;
	read_history(".minishell_history");
	while (1)
	{
		handle_path(&path_splitted, &path_sp_w_slash, env_list);
		set_signals();
		input_status = handle_user_input(&cmd_info, env_list, \
		&shell);
		if (input_status != 0)
			shell.exit_code = execute_command(cmd_info, \
				path_sp_w_slash, env_list);
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
