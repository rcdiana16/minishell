/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 22:28:59 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_standard_builtins(char **command, t_env *env_mini, \
	t_command **cmd_info, char **path)
{
	if (!command)
		return (0);
	if ((ft_strncmp(command[0], "echo", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_echo(command), 1);
	else if ((ft_strncmp(command[0], "cd", ft_strlen(command[0]) + 1)) == 0)
		return (is_valid_path(command[1], env_mini, *cmd_info));
	else if ((ft_strncmp(command[0], "pwd", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_pwd(env_mini), 1);
	else if ((ft_strncmp(command[0], "env", ft_strlen(command[0]) + 1)) == 0)
		return ((ft_our_env(env_mini)), 1);
	else if ((ft_strncmp(command[0], "exit", ft_strlen(command[0]) + 1)) == 0)
		return ((ft_our_exit(env_mini, (*cmd_info)->tokens, \
		*cmd_info, path)), 1);
	else
		return (0);
}

int	check_env_builtins(char **command, t_env *env_mini)
{
	if (!command)
		return (0);
	if ((ft_strncmp(command[0], "export", ft_strlen(command[0]) + 1)) == 0)
	{
		if (command[1] == NULL)
			return (ft_our_env(env_mini), 1);
		else
			ft_export(env_mini, command);
		return (1);
	}
	else if ((ft_strncmp(command[0], "unset", ft_strlen(command[0]) + 1)) == 0)
	{
		if (command[1] != NULL)
			ft_unset(env_mini, command);
		return (1);
	}
	return (0);
}

int	check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
	char **path)
{
	if (!cmd)
		return (0);
	if (check_standard_builtins(cmd, env_mini, &cmd_info, path))
		return (1);
	if (check_env_builtins(cmd_info->tokens, env_mini))
		return (1);
	return (0);
}
