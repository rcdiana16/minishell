/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:13:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 14:37:13 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_tokens(char *cmd)
{
	char	**tokens;
	int		equal_count = 0;
	char	*ptr = cmd;
	char	*first_equal;

	while (*ptr)
	{
		if (*ptr == '=')
			equal_count++;
		ptr++;
	}
	if (equal_count == 1)
	{
		tokens = ft_split(cmd, '=');
	}
	else if (equal_count > 1)
	{
		first_equal = strchr(cmd, '=');
		*first_equal = '\0';
		tokens = ft_split(cmd, ' ');
		char	*rest = first_equal + 1;
		char	**rest_tokens = ft_split(rest, ' ');
		int i = 0, j = 0;
		while (tokens[i]) i++;
		while (rest_tokens[j])
		{
			tokens[i] = rest_tokens[j];
			i++;
			j++;
		}
		tokens[i] = NULL;
		free(rest_tokens);
	}
	else
		tokens = ft_split(cmd, ' ');
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
