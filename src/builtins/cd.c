/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 12:26:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_path(char *path, t_env *env_mini)
{
	char	*oldpwd;

	if (path == NULL)
		return (0);
	if (chdir(path) == 0)
	{
		oldpwd = get_env_value(env_mini, "PWD");
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
		return (1);
	}
	else
		perror("cd: ");
		write(2, path, ft_strlen(path));
	return (0);
}
