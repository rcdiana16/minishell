/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/05/05 16:56:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int	check_standard_builtins(char **command, t_env *env_mini, \
	t_command **cmd_info, char **path)
{
	int	i;

	i = 0;
	if (!command)
		return (0);
	while (command[i])
	{
		if (ft_strncmp(command[i], "", 2) == 0)
		{
			i++;
			continue ;
		}
		if ((ft_strncmp(command[i], "echo", ft_strlen(command[i]) + 1)) == 0)
			return (ft_our_echo(command), 0);
		else if ((ft_strncmp(command[i], "cd", ft_strlen(command[i]) + 1)) == 0)
			return (is_valid_path(command[i + 1], env_mini, *cmd_info, \
			&command[i]));
		else if ((ft_strncmp(command[i], "pwd", ft_strlen(command[i]) + 1)) \
				== 0)
			return (ft_our_pwd(env_mini), 0);
		else if ((ft_strncmp(command[i], "env", ft_strlen(command[i]) + 1)) \
				== 0)
			return ((ft_our_env(env_mini, &command[i])));
		else if ((ft_strncmp(command[i], "exit", ft_strlen(command[i]) + 1)) \
				== 0)
			return ((ft_our_exit(env_mini, (*cmd_info)->tokens, *cmd_info, \
			path)));
		else
			return (-1);
	}
	return (0);
}*/

static int	check_echo(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0]) + 1) == 0)
	{
		ft_our_echo(cmd);
		return (0);
	}
	return (-1);
}

static int	check_cd(char **cmd, t_env *env, t_command *info)
{
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0]) + 1) == 0)
		return (is_valid_path(cmd[1], env, info, &cmd[0]));
	return (-1);
}

static int	check_pwd_env_exit(char **cmd, t_env *env, \
	t_command *info, char **path)
{
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]) + 1) == 0)
	{
		ft_our_pwd(env);
		return (0);
	}
	if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0]) + 1) == 0)
		return (ft_our_env(env, &cmd[0]));
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0]) + 1) == 0)
		return (ft_our_exit(env, info->tokens, info, path));
	return (-1);
}

int	check_standard_builtins(char **command, t_env *env_mini, \
	t_command **cmd_info, char **path)
{
	int	i;
	int	res;

	i = 0;
	if (!command)
		return (0);
	while (command[i])
	{
		if (ft_strncmp(command[i], "", 2) == 0)
		{
			i++;
			continue ;
		}
		res = check_echo(&command[i]);
		if (res != -1)
			return (res);
		res = check_cd(&command[i], env_mini, *cmd_info);
		if (res != -1)
			return (res);
		res = check_pwd_env_exit(&command[i], env_mini, *cmd_info, path);
		if (res != -1)
			return (res);
		return (-1);
	}
	return (0);
}

int	check_env_builtins(char **command, t_env *env_mini)
{
	int	exit;

	exit = 0;
	if (!command || !command[0])
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
	exit = check_env_builtins(cmd, env_mini);
	if (exit != -1)
		return (exit);
	return (-1);
}
