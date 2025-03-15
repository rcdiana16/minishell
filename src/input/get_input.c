/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/03/15 12:01:20 by maximemarti      ###   ########.fr       */
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
