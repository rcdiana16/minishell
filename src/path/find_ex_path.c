/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ex_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:30 by diana             #+#    #+#             */
/*   Updated: 2025/02/28 20:54:22 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**add_slash(char **path_splited)
{
	int		i;
	char	**good_path;

	i = 0;
	good_path = NULL;
	while (path_splited[i])
		i++;
	good_path = malloc(sizeof(char *) * i + 1);
	if (!good_path)
		return (NULL);
	i = 0;
	while (path_splited[i])
	{
		good_path[i] = ft_strjoin(path_splited[i], "/");
		if (!good_path)
			return (NULL);
		i++;
	}
	return (good_path);
}

char	*path_to_exc(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

char	*find_no_builtin(char **good_path, char **command)
{
	int		i;
	char	**tmp_path;

	i = 0;
	while (good_path[i])
		i++;
	tmp_path = malloc(sizeof(char *) * i + ft_strlen(command[0]));
	if (!tmp_path)
		return (NULL);
	i = 0;
	while (good_path[i])
	{
		tmp_path[i] = ft_strjoin(good_path[i], command[0]);
		if (!tmp_path)
			return (NULL);
		i++;
	}
	return (path_to_exc(tmp_path));
}
