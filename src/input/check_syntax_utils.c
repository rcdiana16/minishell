/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:14:53 by diana             #+#    #+#             */
/*   Updated: 2025/04/27 22:16:06 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_initial_syntax(char **cmd, char **bad_token)
{
	if (!cmd[0])
		return (-1);
	if (ft_strncmp(cmd[0], ">>", 3) == 0)
	{
		if (bad_token)
			*bad_token = cmd[0];
		return (2);
	}
	if (ft_strncmp(cmd[0], "'<<'", 5) == 0)
	{
		if (bad_token)
			*bad_token = cmd[0];
		return (3);
	}
	if (ft_strncmp(cmd[0], "|", 2) == 0)
	{
		if (bad_token)
			*bad_token = cmd[0];
		return (0);
	}
	return (-1);
}

int	is_redirection(char *token)
{
	if (!token)
		return (0);
	return (ft_strncmp(token, ">", 1) == 0 || \
			ft_strncmp(token, ">>", 2) == 0 || \
			ft_strncmp(token, "<", 1) == 0 || \
			ft_strncmp(token, "<<", 2) == 0);
}
