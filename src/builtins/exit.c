/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:42 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/13 15:33:06 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, \
		char **path)
{
	int	ex;

	ex = 0;
	if (cmd[1])
		ex = ft_atoi(cmd[1]);
	free_env_list(env_mini);
	free_command(cmd_info);
	free_arr(path);
	set_gcode(EXIT_SUCCESS);
	exit (ex);
}
