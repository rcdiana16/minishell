/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:32:31 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/29 11:17:33 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
void	child_process_handle_redirection(t_pipe_exec_info pipe_exec_info)
{
	int	open_mode;

	if (pipe_exec_info.cmd_info->c_red_o || pipe_exec_info.cmd_info->c_append)
	{
		if (pipe_exec_info.cmd_info->c_append)
			open_mode = 2;
		else
			open_mode = 1;
		pipe_exec_info.cmd_info->fd_out = \
		open_file(pipe_exec_info.cmd_info->file_out, open_mode);
		if (pipe_exec_info.cmd_info->fd_out == -1)
			exit(1);
		dup2(pipe_exec_info.cmd_info->fd_out, STDOUT_FILENO);
		close(pipe_exec_info.cmd_info->fd_out);
	}
}*/
/*
int	child_process_execute_command(t_pipe_exec_info pipe_exec_info)
{
	int	exit_builtin;

	pipe_exec_info.current_command = \
	clean_redir(pipe_exec_info.current_command, pipe_exec_info.cmd_info);
	if (pipe_exec_info.cmd_info->file_out)
		if (!manage_redirection(pipe_exec_info.cmd_info))
		{
			free_arr(pipe_exec_info.current_command);
			exit (0);
		}
		//	exit(0);
	exit_builtin = check_builtins(pipe_exec_info.current_command, \
		pipe_exec_info.env_list, pipe_exec_info.cmd_info, \
		pipe_exec_info.path_sp_w_slash);
	if (exit_builtin != -1)
	{
		free_all(pipe_exec_info.cmd_info, pipe_exec_info.path_sp_w_slash, pipe_exec_info.env_list);
		free_arr(pipe_exec_info.current_command);
		return (exit_builtin);
	}
		//return (exit_builtin);
	execute_child_process_pipe(pipe_exec_info.current_command, \
		pipe_exec_info.path_sp_w_slash, pipe_exec_info.env_list, \
		pipe_exec_info.cmd_info);
	return (127);
}
*/

int	child_process_execute_command(t_pipe_exec_info pipe_exec_info)
{
	int	  exit_builtin;
	char  **tmp_command;
//	char  **old_command;

	//old_command = pipe_exec_info.current_command;
	tmp_command = clean_redir(pipe_exec_info.current_command, pipe_exec_info.cmd_info);
	if (!tmp_command)
		return (1);
	//free_arr(old_command);
	pipe_exec_info.current_command = tmp_command;
	if (pipe_exec_info.cmd_info->file_out || pipe_exec_info.cmd_info->file_in)
	{
		if (!manage_redirection(pipe_exec_info.cmd_info))
		{
			free_arr(pipe_exec_info.current_command);
			exit(0);
		}
	}
	exit_builtin = check_builtins(pipe_exec_info.current_command, pipe_exec_info.env_list, \
				pipe_exec_info.cmd_info, pipe_exec_info.path_sp_w_slash);
	if (exit_builtin != -1)
	{
		free_all(pipe_exec_info.cmd_info, pipe_exec_info.path_sp_w_slash, pipe_exec_info.env_list);
		free_arr(pipe_exec_info.current_command);
		return (exit_builtin);
	}
	execute_child_process_pipe(pipe_exec_info.current_command, pipe_exec_info.path_sp_w_slash, \
			pipe_exec_info.env_list, pipe_exec_info.cmd_info);
	return (127);
}

int	wait_for_child_processes(int *pids, int pipe_count)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i <= pipe_count)
	{
		waitpid(pids[i], &exit_status, 0);
		i++;
	}
	set_signals();
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (0);
}

int	execute_pipes_child_process(t_pipe_exec_info *pipe_exec_info, \
	int *pids, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_child_process_pipe_helper(*pipe_exec_info);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pids[i] = pid;
		if (pipe_exec_info->prev_pipe_fd != -1)
			close(pipe_exec_info->prev_pipe_fd);
		if (i < pipe_exec_info->cmd_info->c_pipe)
			pipe_exec_info->prev_pipe_fd = pipe_exec_info->pipe_fd[0];
		close(pipe_exec_info->pipe_fd[1]);
		free_arr(pipe_exec_info->current_command);
		return (0);
	}
}

int	execute_pipes_loop(t_pipe_exec_info *pipe_exec_info, \
	int *pids, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (i <= cmd_info->c_pipe)
	{
		pipe_exec_info->current_command = get_pipe_command(cmd_info, i);
		if (!pipe_exec_info->current_command)
		{
			free(pids);
			return (1);
		}
		if (i < cmd_info->c_pipe)
			create_pipe(pipe_exec_info->pipe_fd);
		pipe_exec_info->i = i;
		if (execute_pipes_child_process(pipe_exec_info, pids, i) != 0)
		{
			free(pids);
			free_arr(pipe_exec_info->current_command);
			return (1);
		}
		i++;
	}
	pipe_exec_info->current_command = NULL;
	return (0);
}

int	execute_pipes(t_command *cmd_info, char **path_sp_w_slash, t_env *env_list)
{
	t_pipe_exec_info	pipe_exec_info;
	int					pids[26];
	int					return_value;

	//pids = malloc(sizeof(int) * (cmd_info->c_pipe + 1));
	//if (!pids)
	//	return (1);
	pipe_exec_info.prev_pipe_fd = -1;
	pipe_exec_info.path_sp_w_slash = path_sp_w_slash;
	pipe_exec_info.env_list = env_list;
	pipe_exec_info.cmd_info = cmd_info;
	if (execute_pipes_loop(&pipe_exec_info, pids, cmd_info) != 0)
	{
	//	free(pids);
		return (1);
	}
	return_value = wait_for_child_processes(pids, cmd_info->c_pipe);
	//free(pids);
	return (return_value);
}
