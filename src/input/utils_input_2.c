/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:12:44 by diana             #+#    #+#             */
/*   Updated: 2025/04/23 17:39:19 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*initialize_command(t_shell *shell)
{
	t_command	*cmd_info;

	(void)shell;
	cmd_info = NULL;
	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->flag = 0;
	cmd_info->c_red_i = 0;
	cmd_info->here_doc = 0;
	cmd_info->c_red_o = 0;
	cmd_info->quotes_s = 0;
	cmd_info->quotes_d = 0;
	cmd_info->exit_code = 0;
	cmd_info->file_out = NULL;
	cmd_info->file_in = NULL;
	cmd_info->c_append = 0;
	cmd_info->flag_test = 0;
	return (cmd_info);
}

void	handle_single_quotes(t_command *cmd_info, int i)
{
	make_good_cmd(cmd_info->tokens[i]);
}
