/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/03/03 15:32:48 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_redirections(char *cmd, t_command *cmd_info, int *i)
{
	if (!cmd)
		return ;
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

void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			cmd_info->c_pipe++;
		else
			count_redirections(cmd, cmd_info, &i);
		i++;
	}
}

t_command	*verify_and_split_command(char *cmd)
{
	t_command	*cmd_info;

	if (!cmd)
		return (NULL);
	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->c_red_i = 0;
	cmd_info->c_red_o = 0;
	count_special_chars(cmd, cmd_info);
	cmd_info->tokens = ft_split2(cmd, " \t\'\"");
	if (!cmd_info->tokens)
	{
		free_command(cmd_info);
		return (NULL);
	}
	return (cmd_info);
}

t_command	*get_input(void)
{
	char		*line;
	t_command	*cmd_info;

	line = readline("\033[1;32mCBS$ \033[0m");
	if (!line)
		return (NULL);
	cmd_info = verify_and_split_command(line);
	free(line);
	return (cmd_info);
}
