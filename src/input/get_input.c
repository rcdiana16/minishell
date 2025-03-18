/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/03/18 11:10:01 by maximemarti      ###   ########.fr       */
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
		if (has_enclosed_single_quotes(cmd_info->tokens[i]))
			remove_single_quotes(cmd_info->tokens[i]);
		else
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
	int			i;

	cmd_info = initialize_command();
	if (!cmd_info)
		return (NULL);
	count_special_chars(cmd, cmd_info);
	cmd_info->tokens = tokenize_quotes(cmd);
	if (!cmd_info->tokens)
	{
		free_command(cmd_info);
		return (NULL);
	}
	i = 0;
	while (cmd_info->tokens[i])
	{
		count_redirections(cmd_info->tokens[i], cmd_info);
		i++;
	}
	//printf("%d\n", cmd_info->c_pipe);
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
	write_history(".minishell_history");
//	append_history(1, ".minishell_history");
	free(line);
	return (cmd_info);
}
