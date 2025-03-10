/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/03/08 18:21:36 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_standard_builtins(char **command, t_env *env_mini)
{
	if (!command)
		return (0);
	if ((ft_strncmp(command[0], "echo", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_echo(command), 1);
	else if ((ft_strncmp(command[0], "cd", ft_strlen(command[0]) + 1)) == 0)
		return (is_valid_path(command[1], env_mini), 1);
	else if ((ft_strncmp(command[0], "pwd", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_pwd(env_mini), 1);
	else if ((ft_strncmp(command[0], "env", ft_strlen(command[0]) + 1)) == 0)
		return ((ft_our_env(env_mini)), 1);
	else if ((ft_strncmp(command[0], "exit", ft_strlen(command[0]) + 1)) == 0)
	{
		free_env_list(env_mini);
		set_gcode(EXIT_SUCCESS);
		exit (0);
	}
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
		{
			set_gcode(EXIT_SUCCESS);
			return (ft_our_env(env_mini), 1);
		}	
		if (command[2] == NULL)
		{
			ft_export(env_mini, command);
			set_gcode(EXIT_SUCCESS);
		}
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

int	check_builtins(char **cmd, t_env *env_mini)
{
	if (!cmd)
		return (0);
	if (check_standard_builtins(cmd, env_mini))
		return (1);
	if (check_env_builtins(cmd, env_mini))
		return (1);
	return (0);
}
