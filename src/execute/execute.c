/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:32 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/13 15:35:50 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_child_process(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	char	*built_in_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd_info->tokens[0][0] == '/' || \
		ft_strchr(cmd_info->tokens[0], '/') != NULL)
	{
		execve(cmd_info->tokens[0], cmd_info->tokens, \
			convert_env_to_array(env_list));
		perror("execve");
		exit(1);
	}
	built_in_path = find_no_builtin(path_sp_w_slash, cmd_info->tokens);
	if (!built_in_path)
	{
		write(2, "Command not found: ", ft_strlen("Command not found: "));
		write(2, cmd_info->tokens[0], ft_strlen(cmd_info->tokens[0]));
		write(2, "\n", 1);
		free_all(cmd_info, path_sp_w_slash, env_list);
		exit(127);
	}
	execve(built_in_path, cmd_info->tokens, convert_env_to_array(env_list));
	perror("execve");
	exit(1);
	return (0);
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	pid;

	if (check_builtins(cmd_info->tokens, env_list, cmd_info, path_sp_w_slash))
		return (1);
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd_info, path_sp_w_slash, env_list);
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}
