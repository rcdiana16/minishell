/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 09:22:53 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_cd_error(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Not a directory\n", 18);
		close(fd);
	}
	else
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
	}
	return (1);
}

void	update_pwd_env(t_env *env_mini, char *oldpwd, char *path)
{
	char	*cwd;

	cwd = calloc(256, 4);
	if (!oldpwd | !path | !cwd)
		return ;
	if (path[0] == '/')
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

int	is_valid_path(char *path, t_env *env_mini, t_command *cmd_info)
{
	char	*oldpwd;

	if (!path)
	{
		path = get_env_value(env_mini, "HOME");
		if (!path)
			return (0);
	}
	if (chdir(path) == 0)
	{
		oldpwd = get_env_value(env_mini, "PWD");
		update_pwd_env(env_mini, oldpwd, path);
		return (1);
	}
	cmd_info->exit_code = 1;
	return (print_cd_error(path));
}
