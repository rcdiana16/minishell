/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/03/03 12:43:16 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_cd_error(char *path)
{
	if (open(path, O_RDONLY) != -1)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Not a directory\n", 18);
	}
	else
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
	}
	return (0);
}

void	update_pwd_env(t_env *env_mini, char *oldpwd, char *path)
{
	if (!oldpwd | !path)
		return ;
	if (ft_strncmp(path, "..", 2) == 0)
	{
		update_env(env_mini, oldpwd, "PWD", 4);
		update_env(env_mini, oldpwd, "OLDPWD", 3);
	}
	else if (path[0] == '/')
	{
		update_env(env_mini, oldpwd, "OLDPWD", 3);
		update_env(env_mini, path, "PWD", 0);
	}
	else
	{
		update_env(env_mini, oldpwd, "OLDPWD", 3);
		update_env(env_mini, path, "PWD", 1);
	}
}

int	is_valid_path(char *path, t_env *env_mini)
{
	char	*oldpwd;

	if (!path)
		return (0);
	if (chdir(path) == 0)
	{
		oldpwd = get_env_value(env_mini, "PWD");
		update_pwd_env(env_mini, oldpwd, path);
		return (1);
	}
	return (print_cd_error(path));
}
