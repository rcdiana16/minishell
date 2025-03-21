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

char	*make_good_cmd(char *cmd)
{
	char	*tmp;

	remove_single_quotes(cmd);
	tmp = realloc(cmd, ft_strlen(cmd) + 1);
	if (!tmp)
	{
		perror("realloc failed");
		return (cmd);
	}
	cmd = tmp;
	return (cmd);
}

char	*make_good_cmd2(char *cmd)
{
	char	*tmp;

	clean_quotes(cmd);
	tmp = realloc(cmd, ft_strlen(cmd) + 1);
	if (!tmp)
	{
		perror("realloc failed");
		return (cmd);
	}
	return (tmp);
}
