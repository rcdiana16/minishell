/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:32 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/28 14:52:28 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_or_exit(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

char	*find_builtin_or_exit(char **path_sp_w_slash, t_command *cmd_inf, \
		t_env *env_list)
{
	char	*built_in_path;

	built_in_path = find_no_builtin(path_sp_w_slash, cmd_inf->tokens);
	if (!built_in_path)
		exec_builtin_or_exit(cmd_inf->tokens[0], \
		cmd_inf, env_list, path_sp_w_slash);
	return (built_in_path);
}

int	execute_child_process(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	char	*built_in_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_info->tokens[0])
		return (0);
	if (cmd_info->tokens[0][0] == '/' || \
	ft_strchr(cmd_info->tokens[0], '/') != NULL)
	{
		execve(cmd_info->tokens[0], cmd_info->tokens, \
		convert_env_to_array(env_list));
		exec_builtin_or_exit(cmd_info->tokens[0], \
		cmd_info, env_list, path_sp_w_slash);
	}
	built_in_path = find_builtin_or_exit(path_sp_w_slash, cmd_info, env_list);
	execve(built_in_path, cmd_info->tokens, convert_env_to_array(env_list));
	exec_builtin_or_exit(cmd_info->tokens[0], cmd_info, env_list, \
	path_sp_w_slash);
	return (0);
}

int	execute_builtin(t_command *cmd_info, t_env *env_list, \
	char **path_sp_w_slash)
{
	int	exit_builtin;

	exit_builtin = check_builtins(cmd_info->tokens, env_list, \
		cmd_info, path_sp_w_slash);
	if (exit_builtin != -1)
		return (exit_builtin);
	return (-1);
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	pid;
	int	exit_status;
	int	exit_builtin;
	//int	ret;

	
	if (cmd_info->c_pipe >= 1)
		return (execute_pipes(cmd_info, path_sp_w_slash, env_list));
	cmd_info->tokens = clean_redir(cmd_info->tokens, cmd_info);
	if (!manage_redirection(cmd_info))
		return (1);
	//if (ret != 1)
	//	return (0);
	if (cmd_info->flag_test ==1)
		return 1;
	exit_builtin = execute_builtin(cmd_info, env_list, path_sp_w_slash);
	if (exit_builtin != -1)
		return (exit_builtin);
	pid = fork();
	if (pid == 0)
		execute_in_child(cmd_info, path_sp_w_slash, env_list);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &exit_status, 0);
		set_signals();
		if (WIFEXITED(exit_status))
			return (WEXITSTATUS(exit_status));
	}
	return (0);
}
