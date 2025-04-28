/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:47:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/28 11:48:35 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_empty_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(0);
}

void	handle_dotdot_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

void	handle_is_directory(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": Is a directory\n", 17);
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

void	handle_command_found(t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	free_all(cmd_info, path_sp_w_slash, env_list);
	// free_arr(envp);
	exit(126);
}

void	handle_command_not_found(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
	close_fd(cmd_info);
	/* if (envp) to add to cmd info to free it at the end 
		free_arr(envp); */
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}
