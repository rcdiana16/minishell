/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_sp_ch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:28:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 17:29:31 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_skip_next(int *skip_next, int *i)
{
	*skip_next = 0;
	(*i)++;
}

void	handle_special_char(char *cmd, t_command *cmd_info, int *i, int *j)
{
	char	quote;

	quote = cmd[*i];

	// If two consecutive quotes are found, only move i by 1 instead of 2
	if (cmd[*i + 1] == quote)
	{
		(*i)++;  // Skip only the first quote
		return ;
	}

	cmd[*j] = cmd[*i];
	(*j)++;

	if (quote == '\'')
		cmd_info->quotes_s++;
	else if (quote == '\"')
		cmd_info->quotes_d++;
}/*
void	handle_special_char(char *cmd, int *i, int *j, bool *in_single, bool *in_double)
{
	char	quote;

	quote = cmd[*i];

	// Toggle quote flags
	if (quote == '"' && !(*in_single)) 
		*in_double = !(*in_double);
	else if (quote == '\'' && !(*in_double)) 
		*in_single = !(*in_single);
	else
	{
		// Only store the character if it's not a quote inside another quote
		cmd[*j] = cmd[*i];
		(*j)++;
	}

	(*i)++; // Move to the next character
}*/

void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int	i;
	int	j;
	int	skip_next;

	i = 0;
	j = 0;
	skip_next = 0;
	while (cmd[i])
	{
		if (skip_next)
		{
			handle_skip_next(&skip_next, &i);
			continue ;
		}
		if (cmd[i] == '\'' || cmd[i] == '\"')
			handle_special_char(cmd, cmd_info, &i, &j);
		else
		{
			cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	cmd[j] = '\0';
}/*
void	count_special_chars(char *cmd, __attribute__((unused)) t_command *cmd_info)
{
	int		i;
	int		j;
	int		skip_next;
	bool	in_single;
	bool	in_double;

	i = 0;
	j = 0;
	skip_next = 0;
	in_single = false;
	in_double = false;

	while (cmd[i])
	{
		if (skip_next)
		{
			handle_skip_next(&skip_next, &i);
			continue ;
		}
		if (cmd[i] == '\'' || cmd[i] == '\"')
			handle_special_char(cmd, &i, &j, &in_single, &in_double);
		else
		{
			cmd[j] = cmd[i];
			j++;
			i++;
		}
	}
	cmd[j] = '\0';
}*/
/*
void	count_special_chars(char *cmd,__attribute__((unused)) t_command *cmd_info)
{
	int		i;
	int		j;
	char	first_quote;
	bool	has_outer_quotes;

	i = 0;
	j = 0;
	first_quote = '\0';
	has_outer_quotes = false;

	// Detect and remove outer quotes
	if ((cmd[0] == '"' || cmd[0] == '\'') && cmd[strlen(cmd) - 1] == cmd[0])
	{
		first_quote = cmd[0];
		has_outer_quotes = true;
		i++;  // Skip the first quote
	}

	while (cmd[i])
	{
		// If we reach the last character and it's the matching closing quote, remove it
		if (has_outer_quotes && cmd[i + 1] == '\0' && cmd[i] == first_quote)
			break;

		// Remove **both** consecutive identical quotes ("" or '')
		if ((cmd[i] == '"' || cmd[i] == '\'') && cmd[i] == cmd[i + 1])
		{
			i += 2; // Skip **both** quotes
			continue;
		}

		cmd[j++] = cmd[i++];
	}
	cmd[j] = '\0'; // Null-terminate the result
}*/


