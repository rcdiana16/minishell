/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:13:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/27 15:15:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_tokens(char *cmd)
{
	char	**tokens;

	tokens = ft_split(cmd, '=');
	return (tokens);
}

void	join_cmd_values(char **cmd, char **value)
{
	char	*temp;

	if (!cmd || !cmd[1])
		return ;
	if (cmd[0][0] == '\"' || cmd[0][0] == '\'')
	{
		temp = ft_strjoin(*value, " ");
		*value = ft_strjoin(temp, cmd[1]);
		free(temp);
	}
	else
		*value = ft_strdup(cmd[1]);
}
