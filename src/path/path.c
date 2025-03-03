/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:45:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/03 13:57:37 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (split_path(path));
}

char	**split_path(char *path)
{
	char	**path_splited;

	if (!path)
		return (NULL);
	path_splited = ft_split(path, ':');
	if (!path_splited)
		return (NULL);
	return (path_splited);
}
