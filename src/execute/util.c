/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:01:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/27 15:01:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_or_exit_pipe(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}
