/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:11:15 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/18 10:57:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_token_count(t_command *cmd_info)
{
	int	count;

	count = 0;
	while (cmd_info->tokens[count])
		count++;
	return (count);
}

/*
int	has_enclosed_single_quotes(t_command *cmd_info)
{
	int	last_index;

	if (!cmd_info->tokens[1])
		return (0);
	last_index = get_token_count(cmd_info) - 1;
	if (last_index < 0)
		return (0);
	if (cmd_info->tokens[1][0] == '\'' &&
		cmd_info->tokens[last_index] \
		[ft_strlen(cmd_info->tokens[last_index]) - 1] == '\'')
		return (1);
	return (0);
}
*/

bool	has_enclosed_single_quotes(char *token)
{
	int	len;

	if (token == NULL || ft_strlen(token) < 2)
		return (false);
	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (true);
	return (false);
}

void	clean_quotes(char *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (token[j])
	{
		if (token[j] != '\"')
			token[k++] = token[j];
		j++;
	}
	token[k] = '\0';
}

void	remove_single_quotes(char *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (token[j])
	{
		if (token[j] != '\'')
			token[k++] = token[j];
		j++;
	}
	token[k] = '\0';
}

void	delete_quotes(char *token)
{
	remove_single_quotes(token);
	clean_quotes(token);
}
