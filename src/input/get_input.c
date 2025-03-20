/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/03/19 13:30:29 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*verify_and_split_command(char *cmd, t_env *env_mini, \
			t_shell *shell)
{
	t_command	*cmd_info;
	int			i;

	cmd_info = initialize_command(shell);
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
		remove_newline(cmd_info->tokens[i]);
		i++;
	}
	process_tokens(cmd_info, env_mini, shell);
	return (cmd_info);
}

char	*read_command_line(int mode)
{
	if (mode == 0)
		return (readline("\033[1;32mCBS$ \033[0m"));
	else
		return (get_next_line(0));
}

void	handle_eof_or_empty(char *line, t_shell *shell, t_env *env_mini, \
		int mode)
{
	if (!line)
	{
		if (mode == 0)
			write(1, "exit\n", 5);
		free_env_list(env_mini);
		exit(shell->exit_code);
	}
	if (*line == '\0')
		free(line);
}

t_command	*parse_and_store_command(char *line, t_env *env_mini, \
			t_shell *shell)
{
	t_command	*cmd_info;

	cmd_info = verify_and_split_command(line, env_mini, shell);
	if (!cmd_info)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (cmd_info);
}

t_command	*get_input(t_env *env_mini, int mode, t_shell *shell, \
			char **path)
{
	char	*line;

	line = read_command_line(mode);
	if (!line || *line == '\0')
	{
		if (!line && path)
			free_arr(path);
		handle_eof_or_empty(line, shell, env_mini, mode);
		return (NULL);
	}
	add_history(line);
	write_history(".minishell_history");
	return (parse_and_store_command(line, env_mini, shell));
}
