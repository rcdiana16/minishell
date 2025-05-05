/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_and_split_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:21:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 15:45:29 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if ((ft_strncmp(tokens[i], "><", 2) == 0 || ft_strncmp(tokens[i], "<>", 2) == 0 /*|| \
	(ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) > 1)*/))
			copy_normal_token(tokens, new_tokens, &i, &j);
		if ((ft_strncmp(tokens[i], ">>", 2) == 0 && ft_strlen(tokens[i]) > 2) \
		|| (ft_strncmp(tokens[i], "<<", 2) == 0 && ft_strlen(tokens[i]) > 2))
			split_double_redirection(tokens, new_tokens, &i, &j);
		else if ((tokens[i][0] == '>' || tokens[i][0] == '<') && \
			ft_strlen(tokens[i]) > 1 && \
			((tokens[i][1] != '>' && tokens[i][1] != '<') || tokens[i][2] == \
			'\0') && !ft_strchr(tokens[i] + 1, '>') && \
			!ft_strchr(tokens[i] + 1, '<'))
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
	ret = check_syntax(cmd_info->tokens, &bad_token);
	cmd_info = handle_syntax_errors(cmd_info, shell, ret, bad_token);
	if (!cmd_info)
		return (NULL);
	process_tokens(cmd_info, env_mini, shell);
	return (cmd_info);
}
