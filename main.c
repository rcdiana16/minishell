/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 13:48:29 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_code = 0;

int	main(int ac, char **av, char **env)
{
	char		**path_splitted;
	char		**path_sp_w_slash;
	t_command	*cmd_info;
	t_env		*env_list;

	*av = NULL;
	path_splitted = NULL;
	path_sp_w_slash = NULL;
	cmd_info = NULL;
	env_list = NULL;
	if (ac == 0)
		return (1);
	env_list = initialize_environment(env, env_list);
	disable_echoctl();
	while (1)
	{
		set_signals();
		handle_path(&path_splitted, &path_sp_w_slash, env_list);
		if (isatty(STDIN_FILENO))
		{
			if (handle_input(&cmd_info, env_list, 0))
				continue ;
		}
		else
		{
			if (handle_input(&cmd_info, env_list, 1))
				continue ;
		}
		signal(SIGINT, SIG_IGN);
		execute_command(cmd_info, path_sp_w_slash, env_list);
		set_signals();
		if (cmd_info)
			free_command(cmd_info);
	}
	return (0);
}
