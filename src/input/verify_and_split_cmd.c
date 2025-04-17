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
			char *error, int code)
{
	ft_putstr_fd(error, 2);
	if (cmd_info->tokens[1])
	{
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(cmd_info->tokens[1], 2);
		ft_putstr_fd("\'\n", 2);
	}
	shell->exit_code = code;
	free_command(cmd_info);
	return (NULL);
}

t_command	*handle_syntax_errors(t_command *cmd_info, t_shell *shell, int ret)
{
	if (ret == 0 || ret == 2)
		return (handle_token_error(cmd_info, shell, \
			"minishell: syntax error near unexpected token", 2));
	/*if (ret == 2)
		return (handle_token_error(cmd_info, shell, \
			"minishell: >>: command not found, unexpected\n", 2));*/
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

static char	**allocate_new_tokens(char **tokens)
{
	int	total;

	total = 0;
	while (tokens[total])
		total++;
	return (malloc(sizeof(char *) * (total * 2 + 1)));
}

static void	split_double_redirection(char **tokens, \
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

static void	split_single_redirection(char **tokens, \
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

static void	copy_normal_token(char **tokens, char **new_tokens, int *i, int *j)
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
	return (new_tokens);
}

/*
char	**split_joined_redirections(char **tokens)
{
	int		i;
	int		j;
	int		total;
	char	**new_tokens;

	i = 0;
	j = 0;
	total = 0;
	new_tokens = NULL;
	while (tokens[total])
		total++;
	new_tokens = malloc(sizeof(char *) * (total * 2 + 1));
	if (!new_tokens)
		return (NULL);
	while (tokens[i])
	{
		if ((ft_strncmp(tokens[i], ">>", 2) == 0 && ft_strlen(tokens[i]) > 2) || \
		(ft_strncmp(tokens[i], "<<", 2) == 0 && ft_strlen(tokens[i]) > 2))
		{
			char *redir = ft_substr(tokens[i], 0, 2);
			char *rest = ft_strdup(tokens[i] + 2);
			if (rest && rest[0] != '\0')
			{
				new_tokens[j++] = redir;
				new_tokens[j++] = rest;
			}
			else
			{
				free(redir);
				free(rest);
				new_tokens[j++] = ft_strdup(tokens[i]);
			}
		}
		else if ((tokens[i][0] == '>' || tokens[i][0] == '<') && ft_strlen(tokens[i]) > 1 \
		&& ft_strncmp(tokens[i], "<<", 3) != 0 && ft_strncmp(tokens[i], ">>", 3) != 0)
		{
			char *redir = ft_substr(tokens[i], 0, 1);
			char *rest = ft_strdup(tokens[i] + 1);
			if (rest && rest[0] != '\0')
			{
				new_tokens[j++] = redir;
				new_tokens[j++] = rest;
			}
			else
			{
				free(redir);
				free(rest);
				new_tokens[j++] = ft_strdup(tokens[i]);
			}
		}
		else
		{
			new_tokens[j++] = ft_strdup(tokens[i]);
		}
		i++;
	}
	new_tokens[j] = NULL;
	//free_tokens(tokens); // You must define this safely or skip if unsure
	return (new_tokens);
}
*/
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
	cmd_info->tokens = split_joined_redirections(cmd_info->tokens);
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
