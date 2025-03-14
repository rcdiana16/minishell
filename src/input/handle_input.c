/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:21:28 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 20:59:17 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input(t_command **cmd_info, t_env *env_mini, int mode)
{
	*cmd_info = get_input(env_mini, mode);
	if (!*cmd_info)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	if (!(*cmd_info)->tokens || !(*cmd_info)->tokens[0])
	{
		free_command(*cmd_info);
		*cmd_info = NULL;
		return (1);
	}
	return (0);
}
