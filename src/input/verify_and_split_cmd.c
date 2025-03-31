/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:21:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 17:24:35 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*handle_token_error(t_command *cmd_info, t_shell *shell, \
			char *error, int code)
{
	ft_putstr_fd(error, 2);
	shell->exit_code = code;
	free_command(cmd_info);
	return (NULL);
}

t_command	*handle_syntax_errors(t_command *cmd_info, t_shell *shell, int ret)
{
	if (ret == 0)
		return (handle_token_error(cmd_info, shell, \
			"minishell: syntax error near unexpected token\n", 2));
	if (ret == 2)
		return (handle_token_error(cmd_info, shell, \
			"minishell: >>: command not found\n", 127));
	return (cmd_info);
}

int	is_invalid_single_token(char *token)
{
	return (ft_strncmp(token, ">", 1) == 0 || \
	ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, "<<", 2) == 0);
}

void	process_command_tokens(t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd_info->tokens[i])
	{
		count_redirections(cmd_info->tokens[i], cmd_info);
		remove_newline(cmd_info->tokens[i]);
		i++;
	}
}

t_command	*verify_and_split_command(char *cmd, t_env *env_mini, \
			t_shell *shell)
{
	t_command	*cmd_info;
	int			ret;

	cmd_info = initialize_command(shell);
	if (!cmd_info)
		return (NULL);
	count_special_chars(cmd, cmd_info);
	cmd_info->tokens = tokenize_quotes(cmd);
	if (!cmd_info->tokens)
		return (handle_token_error(cmd_info, shell, "", 0));
	process_command_tokens(cmd_info);
	if (cmd_info->tokens[1] == NULL && \
		is_invalid_single_token(cmd_info->tokens[0]))
		return (handle_token_error(cmd_info, shell, \
			"minishell: syntax error near unexpected token `newline'\n", 2));
	ret = check_syntax(cmd_info->tokens);
	cmd_info = handle_syntax_errors(cmd_info, shell, ret);
	if (!cmd_info)
		return (NULL);
	process_tokens(cmd_info, env_mini, shell);
	return (cmd_info);
}
