/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:32:31 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/24 14:18:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_pipe_bounds(t_command *cmd_info, int i, int *start, int *end)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	*start = 0;
	while (cmd_info->tokens[j])
	{
		if (ft_strncmp(cmd_info->tokens[j], "|", 1) == 0)
		{
			count++;
			if (count == i)
				*start = j + 1;
		}
		j++;
	}
	if (count < i)
		return (0);
	*end = *start;
	while (cmd_info->tokens[*end] && \
		ft_strncmp(cmd_info->tokens[*end], "|", 1) != 0)
		(*end)++;
	return (1);
}

char	**get_pipe_command(t_command *cmd_info, int i)
{
	int		start;
	int		end;
	int		j;
	char	**pipe_command;

	if (!get_pipe_bounds(cmd_info, i, &start, &end))
		return (NULL);
	pipe_command = malloc(sizeof(char *) * (end - start + 1));
	if (!pipe_command)
		return (NULL);
	j = 0;
	while (start < end)
	{
		pipe_command[j] = ft_strdup(cmd_info->tokens[start]);
		start++;
		j++;
	}
	pipe_command[j] = NULL;
	return (pipe_command);
}

int	create_pipe(int *pipe_fd)
{
	return (pipe(pipe_fd));
}

void	child_process_setup_io(t_pipe_exec_info pipe_exec_info)
{
	if (pipe_exec_info.prev_pipe_fd != -1)
	{
		dup2(pipe_exec_info.prev_pipe_fd, STDIN_FILENO);
		close(pipe_exec_info.prev_pipe_fd);
	}
	if (pipe_exec_info.i < pipe_exec_info.cmd_info->c_pipe)
	{
		dup2(pipe_exec_info.pipe_fd[1], STDOUT_FILENO);
		close(pipe_exec_info.pipe_fd[1]);
		close(pipe_exec_info.pipe_fd[0]);
	}
}

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
}

int	child_process_execute_command(t_pipe_exec_info pipe_exec_info)
{
	int	exit_builtin;

	exit_builtin = check_builtins(pipe_exec_info.current_command, \
		pipe_exec_info.env_list, pipe_exec_info.cmd_info, \
		pipe_exec_info.path_sp_w_slash);
	if (exit_builtin != -1)
		return (exit_builtin);
	execute_child_process_pipe(pipe_exec_info.current_command, \
		pipe_exec_info.path_sp_w_slash, pipe_exec_info.env_list, \
		pipe_exec_info.cmd_info);
	return (127);
}

int	execute_child_process_pipe_helper(t_pipe_exec_info pipe_exec_info)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_process_setup_io(pipe_exec_info);
	if (pipe_exec_info.i >= pipe_exec_info.cmd_info->c_pipe)
		child_process_handle_redirection(pipe_exec_info);
	return (child_process_execute_command(pipe_exec_info));
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
		return (execute_child_process_pipe_helper(*pipe_exec_info));
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
			return (1);
		if (cmd_info->c_red_o || cmd_info->c_append)
			pipe_exec_info->current_command = \
			clean_redir(pipe_exec_info->current_command, cmd_info);
		if (i < cmd_info->c_pipe)
			create_pipe(pipe_exec_info->pipe_fd);
		pipe_exec_info->i = i;
		if (execute_pipes_child_process(pipe_exec_info, pids, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_pipes(t_command *cmd_info, char **path_sp_w_slash, t_env *env_list)
{
	t_pipe_exec_info	pipe_exec_info;
	int					*pids;
	int					return_value;

	pids = malloc(sizeof(int) * (cmd_info->c_pipe + 1));
	if (!pids)
		return (1);
	pipe_exec_info.prev_pipe_fd = -1;
	pipe_exec_info.path_sp_w_slash = path_sp_w_slash;
	pipe_exec_info.env_list = env_list;
	pipe_exec_info.cmd_info = cmd_info;
	if (execute_pipes_loop(&pipe_exec_info, pids, cmd_info) != 0)
	{
		free(pids);
		return (1);
	}
	return_value = wait_for_child_processes(pids, cmd_info->c_pipe);
	free(pids);
	return (return_value);
}
