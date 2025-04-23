/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/04/23 10:57:57 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_cd_error(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": Not a directory\n", 18);
		close(fd);
	}
	else
	{
		write(2, "minishell: cd: ", 16);
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
	{
		free(cwd);
		return ;
	}
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

int	handle_cd_arguments(char **cmd, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", \
			ft_strlen("cd: too many arguments\n"));
		cmd_info->exit_code = 1;
		return (1);
	}
	return (0);
}

int	is_valid_path(char *path, t_env *env_mini, t_command *cmd_info, char **cmd)
{
	char	*oldpwd;

	if (!path)
	{
		path = get_env_value(env_mini, "HOME");
		if (!path)
			return (0);
	}
	if (handle_cd_arguments(cmd, cmd_info) != 0)
		return (1);
	if (cmd[1] && ft_strncmp(cmd[1], "-", 2) == 0)
	{
		path = get_env_value(env_mini, "OLDPWD");
		if (!path)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			cmd_info->exit_code = 1;
			return (1);
		}
		// Print the directory to which we change (like Bash)
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
	if (chdir(path) == 0)
	{
		oldpwd = get_env_value(env_mini, "PWD");
		update_pwd_env(env_mini, oldpwd, path);
		return (0);
	}
	cmd_info->exit_code = 1;
	return (print_cd_error(path));
}
