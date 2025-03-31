/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:32:15 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 17:39:52 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_append_redirection(char **cmd_tokens, t_command *cmd_info, \
		int *i)
{
	if (cmd_tokens[*i + 1])
	{
		cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
		cmd_info->c_append = 1;
		cmd_info->c_red_o = 0;
		cmd_info->c_red_i = 0;
		*i += 2;
	}
}

void	handle_output_redirection(char **cmd_tokens, t_command *cmd_info, \
		int *i)
{
	if (cmd_tokens[*i + 1] && cmd_tokens[*i + 1][0] != '\0')
	{
		cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
		cmd_info->c_red_o = 1;
		cmd_info->c_append = 0;
		cmd_info->c_red_i = 0;
		*i += 2;
	}
}

void	handle_input_redirection(char **cmd_tokens, t_command *cmd_info, int *i)
{
	if (cmd_tokens[*i + 1] && cmd_tokens[*i + 1][0] != '\0')
	{
		cmd_info->file_in = ft_strdup(cmd_tokens[*i + 1]);
		cmd_info->c_red_i = 1;
		cmd_info->c_append = 0;
		cmd_info->c_red_o = 0;
		*i += 2;
	}
}

void	handle_redirection(char **cmd_tokens, t_command *cmd_info, int *i)
{
	if (ft_strncmp(cmd_tokens[*i], ">>", 2) == 0)
		handle_append_redirection(cmd_tokens, cmd_info, i);
	else if (ft_strncmp(cmd_tokens[*i], ">", 1) == 0)
		handle_output_redirection(cmd_tokens, cmd_info, i);
	else if (ft_strncmp(cmd_tokens[*i], "<<", 2) == 0)
		handle_heredoc_redirection(cmd_tokens, cmd_info, i);
	else if (ft_strncmp(cmd_tokens[*i], "<", 1) == 0)
		handle_input_redirection(cmd_tokens, cmd_info, i);
}
