/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:24:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/01 17:34:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_command(t_command *cmd_info)
{
	int	i;

	if (!cmd_info)
		return ;
	if (cmd_info->tokens)
	{
		i = 0;
		while (cmd_info->tokens[i])
		{
			free(cmd_info->tokens[i]);
			i++;
		}
		free(cmd_info->tokens);
	}
	free(cmd_info);
}

void	free_arr(char **tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		free(tok[i]);
		i++;
	}
	free(tok);
}
