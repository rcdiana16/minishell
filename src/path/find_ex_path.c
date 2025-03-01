/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ex_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:30 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 23:03:02 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_paths(char **path_splited)
{
	int	i;

	i = 0;
	while (path_splited[i])
		i++;
	return (i);
}

char	**allocate_paths_with_slash(char **path_splited, int count)
{
	char	**good_path;
	int		i;

	good_path = malloc(sizeof(char *) * (count + 1));
	if (!good_path)
		return (NULL);
	i = 0;
	while (i < count)
	{
		good_path[i] = ft_strjoin(path_splited[i], "/");
		if (!good_path[i])
		{
			while (--i >= 0)
				free(good_path[i]);
			free(good_path);
			return (NULL);
		}
		i++;
	}
	good_path[i] = NULL;
	return (good_path);
}

char	**add_slash(char **path_splited)
{
	int	count;

	if (!path_splited)
		return (NULL);
	count = count_paths(path_splited);
	return (allocate_paths_with_slash(path_splited, count));
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
	tmp_path = malloc(sizeof(char *) * (i + 1));
	if (!tmp_path)
		return (NULL);
	i = 0;
	while (good_path[i])
	{
		tmp_path[i] = ft_strjoin(good_path[i], command[0]);
		if (!tmp_path[i])
		{
			while (--i >= 0)
				free(tmp_path[i]);
			free(tmp_path);
			return (NULL);
		}
		i++;
	}
	//free_arr(good_path);
	return (path_to_exc(tmp_path));
}
