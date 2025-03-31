/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/31 16:51:49 by maximemarti      ###   ########.fr       */
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
	t_shell *shell, char **path)
{
	set_signals();
	if (isatty(STDIN_FILENO))
	{
		*cmd_info = get_input(env_list, 0, shell, path);
		if (!*cmd_info)
			return (0);
	}
	else
	{
		*cmd_info = get_input(env_list, 1, shell, path);
		if (!*cmd_info)
			return (0);
	}
	return (1);
}

void	initialize_shell(t_env **env_list, char **env, t_shell_data *data)
{
	data->original_stdout = dup(STDOUT_FILENO);
	data->original_stdin = dup(STDIN_FILENO);
	data->shell.exit_code = 0;
	if (init_shell(env, env_list, &data->path_splitted, \
		&data->path_sp_w_slash) == 1)
		exit(EXIT_FAILURE);
}

void	execute_shell_loop(t_env *env_list, char **env)
{
	t_shell_data	data;
	t_command		*cmd_info;
	int				input_status;

	initialize_shell(&env_list, env, &data);
	while (1)
	{
		handle_path(&data.path_splitted, &data.path_sp_w_slash, env_list);
		set_signals();
		input_status = handle_user_input(&cmd_info, env_list, \
			&data.shell, data.path_sp_w_slash);
		if (input_status != 0)
			data.shell.exit_code = \
			execute_command(cmd_info, data.path_sp_w_slash, env_list);
		if ((input_status != 0) && (cmd_info->c_red_o >= 1 || \
			cmd_info->c_append >= 1) && (cmd_info->c_pipe == 0))
			dup2(data.original_stdout, STDOUT_FILENO);
		if ((input_status != 0) && (cmd_info->c_red_i == 1 || \
			cmd_info->here_doc == 1) && (cmd_info->c_pipe == 0))
			dup2(data.original_stdin, STDIN_FILENO);
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
