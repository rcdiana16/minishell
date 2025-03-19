/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/03/19 12:19:06 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_standard_builtins(char **command, t_env *env_mini, \
	t_command **cmd_info, char **path)
{
	if (!command)
		return (0);
	if ((ft_strncmp(command[0], "echo", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_echo(command), 0);
	else if ((ft_strncmp(command[0], "cd", ft_strlen(command[0]) + 1)) == 0)
		return (is_valid_path(command[1], env_mini, *cmd_info));
	else if ((ft_strncmp(command[0], "pwd", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_pwd(env_mini), 0);
	else if ((ft_strncmp(command[0], "env", ft_strlen(command[0]) + 1)) == 0)
		return ((ft_our_env(env_mini, command)));
	else if ((ft_strncmp(command[0], "exit", ft_strlen(command[0]) + 1)) == 0)
		return ((ft_our_exit(env_mini, (*cmd_info)->tokens, \
		*cmd_info, path)), 1);
	else
		return (-1);
}

int	check_env_builtins(char **command, t_env *env_mini)
{
	int	exit;

	exit = 0;
	if (!command)
		return (0);
	if ((ft_strncmp(command[0], "export", ft_strlen(command[0]) + 1)) == 0)
	{
		if (command[1] == NULL)
			return (ft_our_env(env_mini, command));
		else
		{
			exit = ft_export(env_mini, command);
			return (exit);
		}
	}
	else if ((ft_strncmp(command[0], "unset", ft_strlen(command[0]) + 1)) == 0)
	{
		if (command[1] != NULL)
			ft_unset(env_mini, command);
		return (0);
	}
	return (-1);
}

int	check_builtins(char **cmd, t_env *env_mini, t_command *cmd_info, \
	char **path)
{
	int	exit;

	exit = 0;
	if (!cmd)
		return (0);
	exit = check_standard_builtins(cmd, env_mini, &cmd_info, path);
	if (exit != -1)
		return (exit);
	exit = check_env_builtins(cmd_info->tokens, env_mini);
	if (exit != -1)
		return (exit);
	return (-1);
}
