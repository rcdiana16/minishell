/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:55:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/15 17:55:44 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_strjoin_arr(char *first, char **arr)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	while (arr && arr[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[0] = ft_strdup(first);
	i = 0;
	while (i < len)
	{
		new_arr[i + 1] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[len + 1] = NULL;
	free_arr(arr);
	return (new_arr);
}

void	count_redirections(char *cmd, t_command *cmd_info, int *i)
{
	if (cmd[*i] == '<')
	{
		if (cmd[*i + 1] == '<')
		{
			cmd_info->here_doc++;
			(*i)++;
		}
		else
			cmd_info->c_red_i++;
	}
	else if (cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '>')
		{
			cmd_info->c_append++;
			(*i)++;
		}
		else
			cmd_info->c_red_o++;
	}
}
