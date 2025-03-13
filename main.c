/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/13 15:26:51 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	g_code = 0;

void	handle_path(char ***path_splitted, char ***path_sp_w_slash, \
	t_env *env_mini)
{
	if (*path_sp_w_slash)
		free_arr(*path_sp_w_slash);
	*path_splitted = get_path(env_mini);
	if (!*path_splitted)
	{
		write(2, "Error: get_path() returned NULL\n", \
			ft_strlen("Error: get_path() returned NULL\n"));
		exit(1);
	}
	*path_sp_w_slash = add_slash(*path_splitted);
	free_arr(*path_splitted);
	if (!*path_sp_w_slash)
	{
		write(2, "Error: add_slash() returned NULL\n", \
			ft_strlen("Error: add_slash() returned NULL\n"));
		exit(1);
	}
}

int	handle_input(t_command **cmd_info, t_env *env_mini, int mode)
{
	*cmd_info = get_input(env_mini, mode);
	if (!*cmd_info || !(*cmd_info)->tokens || !(*cmd_info)->tokens[0])
	{
		free_command(*cmd_info);
		return (1);
	}
	return (0);
}

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
	set_signals();
	while (1)
	{
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
		execute_command(cmd_info, path_sp_w_slash, env_list);
		if (cmd_info)
			free_command(cmd_info);
		//if (path_sp_w_slash)
			//free_arr(path_sp_w_slash);
		//free_arr(path_splitted);
		//free_env_list(env_list);
	}
	return (0);
}

int	get_gcode(void)
{
	return (g_code);
}

void	set_gcode(int val)
{
	g_code = val;
}
