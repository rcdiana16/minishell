/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/03/15 17:55:40 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	split_command(char *cmd, t_command *cmd_info)
{
	char	*first_space;
	char	*first_part;
	char	*rest;

	first_space = ft_strchr(cmd, ' ');
	if (first_space)
	{
		first_part = ft_substr(cmd, 0, first_space - cmd);
		rest = first_space + 1;
		cmd_info->tokens = ft_split2(rest, "\'\"");
	}
	else
	{
		first_part = ft_strdup(cmd);
		cmd_info->tokens = NULL;
	}
	if (cmd_info->tokens)
		cmd_info->tokens = ft_strjoin_arr(first_part, cmd_info->tokens);
	else
		cmd_info->tokens = ft_split2(first_part, "\'\"");
	free(first_part);
}

t_command	*verify_and_split_command(char *cmd, t_env *env_mini)
{
	t_command	*cmd_info;

	cmd_info = initialize_command();
	if (!cmd_info)
		return (NULL);
	count_special_chars(cmd, cmd_info);
	if (cmd_info->quotes_s != 0 || cmd_info->quotes_d != 0)
		split_command(cmd, cmd_info);
	else
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
		return (NULL);
	cmd_info = verify_and_split_command(line, env_mini);
	if (!cmd_info)
		return (NULL);
	add_history(line);
	free(line);
	return (cmd_info);
}
