/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:12:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/18 17:05:35 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*initialize_command(t_shell *shell)
{
	t_command	*cmd_info;

	(void)shell;
	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->flag = 0;
	cmd_info->c_red_i = 0;
	cmd_info->c_red_o = 0;
	cmd_info->quotes_s = 0;
	cmd_info->quotes_d = 0;
	cmd_info->exit_code = 0;
	cmd_info->file_out = NULL;
	cmd_info->c_append = 0;
	return (cmd_info);
}

void	process_tokens(t_command *cmd_info, t_env *env_mini, t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;
	char	*new_cmd;

	if (!cmd_info->tokens || !cmd_info->tokens[0])
		return ;
	i = 0;
	while (cmd_info->tokens[i])
	{
		if (has_enclosed_single_quotes(cmd_info->tokens[i]))
			make_good_cmd(cmd_info->tokens[i]);
		else
		{
			new_cmd = make_good_cmd2(cmd_info->tokens[i]);
			if (new_cmd)
				cmd_info->tokens[i] = new_cmd;
			tmp = replace_env_vars(cmd_info->tokens[i], env_mini, shell);
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
				continue ;
			}
		}
		i++;
	}
}

void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			cmd_info->quotes_s++;
		else if (cmd[i] == '\"')
			cmd_info->quotes_d++;
		i++;
	}
}

void	remove_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
