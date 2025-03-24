/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:32 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/24 15:29:00 by maximemarti      ###   ########.fr       */
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

char	**check_redir(t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd_info->tokens[i])
		i++;
	if ((cmd_info->c_red_o == 1 || cmd_info->c_append == 1) && i >= 2)
	{
		cmd_info->file_out = ft_strdup(cmd_info->tokens[i - 1]);
		free(cmd_info->tokens[i - 2]);
		cmd_info->tokens[i - 2] = NULL;
		free(cmd_info->tokens[i - 1]);
		cmd_info->tokens[i - 1] = NULL;
		cmd_info->tokens[i - 2] = cmd_info->tokens[i];
		cmd_info->tokens[i - 1] = NULL;
	}
	return (cmd_info->tokens);
}

int	open_file(char *file, int mode)
{
	int	fd;

	fd = 0;
	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, file, ft_strlen(file));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		return (-1);
	}
	return (fd);
}

int	manage_redirection(t_command *cmd_info)
{
	if (cmd_info->c_red_o == 1 || cmd_info->c_append == 1)
	{
		if (cmd_info->c_red_o == 1)
			cmd_info->fd_out = open_file(cmd_info->file_out, 1);
		else if (cmd_info->c_append == 1)
			cmd_info->fd_out = open_file(cmd_info->file_out, 2);
		if (cmd_info->fd_out == -1)
			return (0);
		dup2(cmd_info->fd_out, STDOUT_FILENO);
		close(cmd_info->fd_out);
	}
	return (1);
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

void	execute_in_child(t_command *cmd_info, \
	char **path_sp_w_slash, t_env *env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_child_process(cmd_info, path_sp_w_slash, env_list);
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	pid;
	int	exit_status;
	int	exit_builtin;

	if (cmd_info->c_pipe >= 1)
		return (execute_pipes(cmd_info, path_sp_w_slash, env_list));
	cmd_info->tokens = check_redir(cmd_info);
	if (!manage_redirection(cmd_info))
		return (0);
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
