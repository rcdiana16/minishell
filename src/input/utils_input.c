/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:12:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/04/23 11:15:55 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
void	handle_double_quotes_and_env_vars(t_command *cmd_info, t_env *env_mini, \
	t_shell *shell, int i)
{
	char	*new_cmd;
	char	*tmp;
	int		j;

	new_cmd = make_good_cmd2(cmd_info->tokens[i]);
	if (new_cmd)
		cmd_info->tokens[i] = new_cmd;
	if (cmd_info->tokens[i][0] == '$' && cmd_info->tokens[i][1] == ' ')
		return ;
	tmp = replace_env_vars(cmd_info->tokens[i], env_mini, shell);
	if (tmp == NULL && cmd_info->c_red_o > 0)
	{
		cmd_info->flag_test = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_info->tokens[i], 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return ;
	}
	if (tmp && tmp[0] != '\0')
	{
		free(cmd_info->tokens[i]);
		cmd_info->tokens[i] = tmp;
	}
	else
	{
		free(cmd_info->tokens[i]);
		free(tmp);
		j = i;
		while (cmd_info->tokens[j])
		{
			cmd_info->tokens[j] = cmd_info->tokens[j + 1];
			j++;
		}
		cmd_info->tokens[j] = NULL;
	}
}
*/

static int	prepare_token(t_command *cmd_info, int i)
{
	char	*new_cmd;

	new_cmd = make_good_cmd2(cmd_info->tokens[i]);
	if (new_cmd)
		cmd_info->tokens[i] = new_cmd;
	if (cmd_info->tokens[i][0] == '$' && cmd_info->tokens[i][1] == ' ')
		return (0);
	return (1);
}

static int	check_ambiguous_redirect(t_command *cmd_info, char *token)
{
	if (cmd_info->c_red_o > 0)
	{
		cmd_info->flag_test = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (1);
	}
	return (0);
}

static void	replace_or_remove_token(t_command *cmd_info, int i, char *tmp)
{
	int	j;

	if (tmp && tmp[0] != '\0')
	{
		free(cmd_info->tokens[i]);
		cmd_info->tokens[i] = tmp;
	}
	else
	{
		free(cmd_info->tokens[i]);
		free(tmp);
		j = i;
		while (cmd_info->tokens[j])
		{
			cmd_info->tokens[j] = cmd_info->tokens[j + 1];
			j++;
		}
		cmd_info->tokens[j] = NULL;
	}
}

static void	handle_env_var_replacement(t_command *cmd_info, \
			t_env *env_mini, t_shell *shell, int i)
{
	char	*tmp;

	tmp = replace_env_vars(cmd_info->tokens[i], env_mini, shell);
	if (tmp == NULL)
	{
		if (check_ambiguous_redirect(cmd_info, cmd_info->tokens[i]))
			return ;
	}
	replace_or_remove_token(cmd_info, i, tmp);
}

void	process_tokens(t_command *cmd_info, t_env *env_mini, t_shell *shell)
{
	int	i;

	if (!cmd_info->tokens || !cmd_info->tokens[0])
		return ;
	i = 0;
	while (cmd_info->tokens[i])
	{
		if (has_enclosed_single_quotes(cmd_info->tokens[i]))
			handle_single_quotes(cmd_info, i);
		else
			handle_double_quotes_and_env_vars(cmd_info, env_mini, shell, i);
		i++;
	}
}

/*
void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int		i;
	int		j;
	char	quote;
	int		skip_next;

	i = 0;
	j = 0;
	skip_next = 0;
	while (cmd[i])
	{
		if (skip_next)
		{
			skip_next = 0;
			i++;
			continue ;
		}
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote = cmd[i];
			if (cmd[i + 1] == quote)
				skip_next = 1;
			else
			{
				cmd[j] = cmd[i];
				j++;
				if (quote == '\'')
					cmd_info->quotes_s++;
				else if (quote == '\"')
					cmd_info->quotes_d++;
			}
		}
		else
		{
			cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	cmd[j] = '\0';
}*/
