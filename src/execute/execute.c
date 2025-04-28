/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:32 by cosmos            #+#    #+#             */
/*   Updated: 2025/04/27 21:54:50 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
void	exec_builtin_or_exit(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	if (open(command, O_RDONLY) != -1)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, command, ft_strlen(command));
		write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));	
		free_all(cmd_info, path_sp_w_slash, env_list);
		exit(126);
	}
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));	
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}*/
/*
void	exec_builtin_or_exit(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	struct stat	info;

	if (ft_strncmp(command, "", 2) == 0)
	{
		close_fd(cmd_info);
		free_all(cmd_info, path_sp_w_slash, env_list);
		exit(0);
	}
	else if (ft_strncmp(command, "..", 3) == 0)
	{
		free_all(cmd_info, path_sp_w_slash, env_list);
		exit(127);
	}
	else if (stat(command, &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
		{
			write(2, "minishell: ", ft_strlen("minishell: "));
			write(2, command, ft_strlen(command));
			write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
			close_fd(cmd_info);	
			free_all(cmd_info, path_sp_w_slash, env_list);
			exit(127);
		}
		free_all(cmd_info, path_sp_w_slash, env_list);
		//free_arr(envp);
		exit(126);
	}
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	close_fd(cmd_info);
	if (envp) to add to cmd info to free it at the end 
		free_arr(envp);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}*/

static void	handle_empty_command(t_command *cmd_info, char **path_sp_w_slash, \
		t_env *env_list)
{
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(0);
}

static void	handle_dotdot_command(t_command *cmd_info, char **path_sp_w_slash, \
		t_env *env_list)
{
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

static void	handle_is_directory(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": Is a directory\n", 17);
	close_fd(cmd_info);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

static void	handle_command_found(t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	free_all(cmd_info, path_sp_w_slash, env_list);
	// free_arr(envp);
	exit(126);
}

static void	handle_command_not_found(char *command, t_command *cmd_info, \
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

void	exec_builtin_or_exit(char *command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	struct stat	info;

	if (ft_strncmp(command, "", 2) == 0)
		handle_empty_command(cmd_info, path_sp_w_slash, env_list);
	else if (ft_strncmp(command, "..", 3) == 0)
		handle_dotdot_command(cmd_info, path_sp_w_slash, env_list);
	else if (stat(command, &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			handle_is_directory(command, cmd_info, env_list, path_sp_w_slash);
		handle_command_found( cmd_info, env_list, path_sp_w_slash);
	}
	handle_command_not_found(command, cmd_info, env_list, path_sp_w_slash);
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
	//char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_info->tokens[0])
		return (0);
	cmd_info->envp = convert_env_to_array(env_list);
	if (cmd_info->tokens[0][0] == '/' || \
	ft_strchr(cmd_info->tokens[0], '/') != NULL)
	{
		execve(cmd_info->tokens[0], cmd_info->tokens, \
		cmd_info->envp);
		//free_arr (cmd_info->envp);
		exec_builtin_or_exit(cmd_info->tokens[0], \
		cmd_info, env_list, path_sp_w_slash);
	}
	built_in_path = find_builtin_or_exit(path_sp_w_slash, cmd_info, \
	env_list);
	execve(built_in_path, cmd_info->tokens, cmd_info->envp);
	//free_arr(envp);
	free(built_in_path);
	exec_builtin_or_exit(cmd_info->tokens[0], cmd_info, env_list, \
	path_sp_w_slash);
	return (0);
}

/*int	execute_builtin(t_command *cmd_info, t_env *env_list, \
	char **path_sp_w_slash)
{
	int	exit_builtin;

	exit_builtin = check_builtins(cmd_info->tokens, env_list, \
		cmd_info, path_sp_w_slash);
	if (exit_builtin != -1)
		return (exit_builtin);
	return (-1);
}*/
/*
int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	pid;
	int	exit_status;
	int	exit_builtin;

	if (cmd_info->c_pipe >= 1)
		return (execute_pipes(cmd_info, path_sp_w_slash, env_list));
	cmd_info->tokens = clean_redir(cmd_info->tokens, cmd_info);
	if (!manage_redirection(cmd_info))
		return (1);
	if (cmd_info->flag_test == 1)
		return (1);
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
*/

int	prepare_execution(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	exit_builtin;

	if (cmd_info->c_pipe >= 1)
		return (execute_pipes(cmd_info, path_sp_w_slash, env_list));
	cmd_info->tokens = clean_redir(cmd_info->tokens, cmd_info);
	if (!manage_redirection(cmd_info))
		return (1);
	if (cmd_info->flag_test == 1)
		return (1);
	exit_builtin = execute_builtin(cmd_info, env_list, path_sp_w_slash);
	if (exit_builtin != -1)
		return (exit_builtin);
	return (-1);
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	pid;
	int	exit_status;
	int	prepare_status;

	prepare_status = prepare_execution(cmd_info, path_sp_w_slash, env_list);
	if (prepare_status != -1)
		return (prepare_status);
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
