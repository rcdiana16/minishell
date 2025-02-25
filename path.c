/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:45:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/02/25 13:43:08 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i];
		i++;
	}
	return (split_path(path + 5));
}

char	**split_path(char *path)
{
	char	**path_splited;

	path_splited = ft_split(path, ':');
	return (path_splited);
}
