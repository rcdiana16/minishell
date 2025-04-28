/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/27 21:26:45 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
void	exec_builtin_or_exit_pipe(char **command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	free_all(cmd_info, path_sp_w_slash, env_list);
	free_arr(command);
	//free_arr(envp);
	exit(127);
}*/

void	exec_builtin_or_exit_pipe(char **command, t_command *cmd_info, \
		t_env *env_list, char **path_sp_w_slash)
{
	struct stat	info;

	if (ft_strncmp(command[0], "", 2) == 0)
	{
		if (cmd_info->og_stdin != -1)
		{
			close(cmd_info->og_stdin);
			cmd_info->og_stdin = -1;
		}
		if (cmd_info->og_stdout != -1)
		{
			close(cmd_info->og_stdout);
			cmd_info->og_stdout = -1;
		}
		free_all(cmd_info, path_sp_w_slash, env_list);
		free_arr(command);
		exit(0);
	}
	if (ft_strncmp(command[0], "..", 3) == 0)
	{
		free_all(cmd_info, path_sp_w_slash, env_list);
		free_arr(command);
		exit(127);
	}
	if (stat(command[0], &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
		{
			write(2, "minishell: ", ft_strlen("minishell: "));
			write(2, command[0], ft_strlen(command[0]));
			write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
			if (cmd_info->og_stdin != -1)
			{
				close(cmd_info->og_stdin);
				cmd_info->og_stdin = -1;
			}
			if (cmd_info->og_stdout != -1)
			{
				close(cmd_info->og_stdout);
				cmd_info->og_stdout = -1;
			}
			free_all(cmd_info, path_sp_w_slash, env_list);
			free_arr(command);
			exit(126);
		}
	}
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	if (cmd_info->og_stdin != -1)
	{
		close(cmd_info->og_stdin);
		cmd_info->og_stdin = -1;
	}
	if (cmd_info->og_stdout != -1)
	{
		close(cmd_info->og_stdout);
		cmd_info->og_stdout = -1;
	}
	free_arr(command);
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
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
