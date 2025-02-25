/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:45:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/02/25 19:06:48 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	char	*path;

	path = get_env("PATH", env);
	if (!path)
		return (NULL);
	return (split_path(path));
}

char	**split_path(char *path)
{
	char	**path_splited;

	path_splited = ft_split(path, ':');
	if (!path_splited)
		return (NULL);
	return (path_splited);
}
