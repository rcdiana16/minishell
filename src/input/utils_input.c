/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:12:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/13 17:41:34 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*initialize_command(void)
{
	t_command	*cmd_info;

	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->flag = 0;
	cmd_info->c_red_i = 0;
	cmd_info->c_red_o = 0;
	return (cmd_info);
}

void	process_tokens(t_command *cmd_info, t_env *env_mini)
{
	int		i;
	char	*tmp;

	if (cmd_info->tokens[1] && cmd_info->tokens[1][0] == '\'' &&
		cmd_info->tokens[1][ft_strlen(cmd_info->tokens[1]) - 1] == '\'')
		cmd_info->flag = 1;
	i = 0;
	if (cmd_info->flag != 0)
		make_good_cmd(cmd_info);
	else
	{
		while (cmd_info->tokens[i])
		{
			tmp = replace_env_vars(cmd_info->tokens[i], env_mini);
			if (tmp)
			{
				free(cmd_info->tokens[i]);
				cmd_info->tokens[i] = tmp;
			}
			i++;
		}
		make_good_cmd2(cmd_info);
	}
}

void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			cmd_info->c_pipe++;
		else
			count_redirections(cmd, cmd_info, &i);
		i++;
	}
}

void	clean_quotes(char *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (token[j])
	{
		if (token[j] != '\"')
			token[k++] = token[j];
		j++;
	}
	token[k] = '\0';
}

void	remove_single_quotes(char *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (token[j])
	{
		if (token[j] != '\'')
			token[k++] = token[j];
		j++;
	}
	token[k] = '\0';
}
