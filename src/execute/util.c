/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 17:20:39 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_or_exit_pipe(char **command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	free_all(cmd_info, path_sp_w_slash, env_list);
	free_arr(command);
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
