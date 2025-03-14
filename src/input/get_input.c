/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 13:53:31 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_command	*make_good_cmd(t_command *cmd_info)
{
	int		i;
	char	*tmp;

	i = 1;
	while (cmd_info->tokens[i])
	{
		remove_single_quotes(cmd_info->tokens[i]);
		tmp = realloc(cmd_info->tokens[i], ft_strlen(cmd_info->tokens[i]) + 1);
		if (!tmp)
		{
			perror("realloc failed");
			return (cmd_info);
		}
		cmd_info->tokens[i] = tmp;
		i++;
	}
	return (cmd_info);
}

t_command	*make_good_cmd2(t_command *cmd_info)
{
	int		i;
	char	*tmp;

	i = 1;
	while (cmd_info->tokens[i])
	{
		clean_quotes(cmd_info->tokens[i]);
		tmp = realloc(cmd_info->tokens[i], ft_strlen(cmd_info->tokens[i]) + 1);
		if (!tmp)
		{
			perror("realloc failed");
			return (cmd_info);
		}
		cmd_info->tokens[i] = tmp;
		i++;
	}
	return (cmd_info);
}

t_command	*verify_and_split_command(char *cmd, t_env *env_mini)
{
	t_command	*cmd_info;

	cmd_info = initialize_command();
	if (!cmd_info)
		return (NULL);
	count_special_chars(cmd, cmd_info);
	cmd_info->tokens = ft_split2(cmd, " \t");
	if (!cmd_info->tokens)
	{
		free_command(cmd_info);
		return (NULL);
	}
	process_tokens(cmd_info, env_mini);
	return (cmd_info);
}

t_command	*get_input(t_env *env_mini, int mode)
{
	char		*line;
	t_command	*cmd_info;

	if (mode == 0)
		line = readline("\033[1;32mCBS$ \033[0m");
	else
		line = get_next_line(0);
	if (!line)
		exit(0);
	cmd_info = verify_and_split_command(line, env_mini);
	if (!cmd_info)
		return (NULL);
	add_history(line);
	free(line);
	return (cmd_info);
}
