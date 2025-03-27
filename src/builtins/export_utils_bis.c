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

char	**get_tokens(char **cmd)
{
	char	**tokens;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	i--;
	if (i == 1)
		tokens = ft_split(cmd[1], '=');
	else
		tokens = ft_split(cmd[2], ' ');
	return (tokens);
}

void	join_cmd_values(char **cmd, char **value)
{
	if (!cmd || !cmd[1])
		return ;
	if (cmd[1][0] == '\"' || cmd[1][0] == '\'')
		join_quoted_values(cmd, value);
	else if (cmd[2])
		assign_value(cmd, value);
}
