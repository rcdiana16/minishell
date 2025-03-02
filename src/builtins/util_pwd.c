/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:06:29 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/02 16:07:13 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_our_pwd(t_env *env_mini)
{
	char	*pwd;

	pwd = get_env_value(env_mini, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("pwd: no such variable");
}

char	*ft_find_dir(char *path)
{
	int	i;
	int	c_slash;

	c_slash = 0;
	i = ft_strlen(path) - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			c_slash = i;
			break ;
		}
		i--;
	}
	return (path + c_slash);
}

char	*ft_find_gd_dir(char *path)
{
	int		i;
	int		c_slash;
	char	*good_path;

	i = ft_strlen(path) - 1;
	c_slash = 0;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			c_slash = i;
			break ;
		}
		i--;
	}
	good_path = ft_strndup(path, c_slash);
	return (good_path);
}
