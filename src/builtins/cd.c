/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/03/08 18:52:38 by diana            ###   ########.fr       */
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
	set_gcode(EXIT_FAILURE);
	return (0);
}

void	update_pwd_env(t_env *env_mini, char *oldpwd, char *path)
{
	char	*cwd;

	cwd = calloc(256, 4);
	if (!oldpwd | !path | !cwd)
		return ;
	if (ft_strncmp(path, "..", 2) == 0)
	{
		update_env(env_mini, oldpwd, "PWD", 4);
		update_env(env_mini, oldpwd, "OLDPWD", 3);
	}
	else if (path[0] == '/')
	{
		update_env(env_mini, oldpwd, "OLDPWD", 3);
		update_env(env_mini, getcwd(cwd, 1024), "PWD", 1);
	}
	else
	{
		update_env(env_mini, oldpwd, "OLDPWD", 3);
		update_env(env_mini, getcwd(cwd, 1024), "PWD", 1);
	}
	free(cwd);
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
		set_gcode(EXIT_SUCCESS);
		return (1);
	}
	return (print_cd_error(path));
}
