/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:21:28 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/19 13:31:23 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*make_good_cmd(t_command *cmd_info)
{
	int		i;
	char	*tmp;

	i = 1;
	while (cmd_info->tokens[i])
	{
		if (has_enclosed_single_quotes(cmd_info->tokens[i]))
			remove_single_quotes(cmd_info->tokens[i]);
		else
			clean_quotes(cmd_info->tokens[i]);
		tmp = realloc(cmd_info->tokens[i], ft_strlen(cmd_info->tokens[i]) + 1);
		if (!tmp)
		{
			perror("realloc failed");
			return (cmd_info);
		}
		cmd_info->tokens[i] = tmp;
		i++;
	}
	return (cmd_info);
}

t_command	*make_good_cmd2(t_command *cmd_info)
{
	int		i;
	char	*tmp;

	i = 1;
	while (cmd_info->tokens[i])
	{
		clean_quotes(cmd_info->tokens[i]);
		tmp = realloc(cmd_info->tokens[i], ft_strlen(cmd_info->tokens[i]) + 1);
		if (!tmp)
		{
			perror("realloc failed");
			return (cmd_info);
		}
		cmd_info->tokens[i] = tmp;
		i++;
	}
	return (cmd_info);
}
