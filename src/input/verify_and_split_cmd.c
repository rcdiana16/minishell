/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:21:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/17 22:20:10 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*handle_token_error(t_command *cmd_info, t_shell *shell, \
			 int code, char *bad_token)
{
	if (!bad_token)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	if (bad_token)
	{
		ft_putstr_fd(" `", 2);
		if (ft_strlen(bad_token) > 2)
			write(2, bad_token, 2);
		else if (ft_strlen(bad_token) == 1)
			write(2, bad_token, 1);
		else
			ft_putstr_fd(bad_token, 2);
		ft_putstr_fd("'\n", 2);
	}
	shell->exit_code = code;
	free_command(cmd_info);
	return (NULL);
}

t_command	*handle_syntax_errors(t_command *cmd_info, t_shell *shell, int ret, char *bad_token)
{
	if (ret == 0 || ret == 2)
		return (handle_token_error(cmd_info, shell, \
			 2, bad_token));
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

char	**allocate_new_tokens(char **tokens)
{
	int	total;

	total = 0;
	while (tokens[total])
		total++;
	return (malloc(sizeof(char *) * (total * 2 + 1)));
}

void	split_double_redirection(char **tokens, \
	char **new_tokens, int *i, int *j)
{
	char	*redir;
	char	*rest;

	redir = ft_substr(tokens[*i], 0, 2);
	rest = ft_strdup(tokens[*i] + 2);
	if (rest && rest[0] != '\0')
	{
		new_tokens[(*j)++] = redir;
		new_tokens[(*j)++] = rest;
	}
	else
	{
		free(redir);
		free(rest);
		new_tokens[(*j)++] = ft_strdup(tokens[*i]);
	}
}

void	split_single_redirection(char **tokens, \
			char **new_tokens, int *i, int *j)
{
	char	*redir;
	char	*rest;

	redir = ft_substr(tokens[*i], 0, 1);
	rest = ft_strdup(tokens[*i] + 1);
	if (rest && rest[0] != '\0')
	{
		new_tokens[(*j)++] = redir;
		new_tokens[(*j)++] = rest;
	}
	else
	{
		free(redir);
		free(rest);
		new_tokens[(*j)++] = ft_strdup(tokens[*i]);
	}
}

void	copy_normal_token(char **tokens, char **new_tokens, int *i, int *j)
{
	new_tokens[(*j)++] = ft_strdup(tokens[*i]);
}

char	**split_joined_redirections(char **tokens)
{
	int		i;
	int		j;
	char	**new_tokens;

	i = 0;
	j = 0;
	new_tokens = allocate_new_tokens(tokens);
	if (!new_tokens)
		return (NULL);
	while (tokens[i])
	{
		if ((ft_strncmp(tokens[i], ">>", 2) == 0 && ft_strlen(tokens[i]) > 2) \
		|| (ft_strncmp(tokens[i], "<<", 2) == 0 && ft_strlen(tokens[i]) > 2))
			split_double_redirection(tokens, new_tokens, &i, &j);
		else if ((tokens[i][0] == '>' || tokens[i][0] == '<') && \
		ft_strlen(tokens[i]) > 1 && ft_strncmp(tokens[i], "<<", 3) \
		!= 0 && ft_strncmp(tokens[i], ">>", 3) != 0)
			split_single_redirection(tokens, new_tokens, &i, &j);
		else
			copy_normal_token(tokens, new_tokens, &i, &j);
		i++;
	}
	new_tokens[j] = NULL;
	free_arr(tokens);
	return (new_tokens);
}

t_command	*verify_and_split_command(char *cmd, t_env *env_mini, \
			t_shell *shell)
{
	t_command	*cmd_info;
	int			ret;
	char		*bad_token;

	bad_token = NULL;
	cmd_info = initialize_command(shell);
	if (!cmd_info)
		return (NULL);
	count_special_chars(cmd, cmd_info);
	cmd_info->tokens = tokenize_quotes(cmd);
	if (!cmd_info->tokens)
		return (handle_token_error(cmd_info, shell, 0, NULL));
	process_command_tokens(cmd_info);
	cmd_info->tokens = split_joined_redirections(cmd_info->tokens);
	if (cmd_info->tokens[1] == NULL && \
		is_invalid_single_token(cmd_info->tokens[0]))
		return (handle_token_error(cmd_info, shell, \
			 2, NULL));
	ret = check_syntax(cmd_info->tokens, &bad_token); // pass bad_token
	cmd_info = handle_syntax_errors(cmd_info, shell, ret, bad_token);
	if (!cmd_info)
		return (NULL);
	process_tokens(cmd_info, env_mini, shell);
	return (cmd_info);
}


