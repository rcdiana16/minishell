/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ex_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:30 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 11:13:24 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*path_to_exc(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

char	**build_command_paths(char **good_path, char *command)
{
	int		i;
	char	**tmp_path;

	if (!good_path || !command)
		return (NULL);
	i = count_paths(good_path);
	tmp_path = malloc(sizeof(char *) * (i + 1));
	if (!tmp_path)
		return (NULL);
	i = 0;
	while (good_path[i])
	{
		tmp_path[i] = ft_strjoin(good_path[i], command);
		if (!tmp_path[i])
		{
			while (--i >= 0)
				free(tmp_path[i]);
			free(tmp_path);
			return (NULL);
		}
		i++;
	}
	tmp_path[i] = NULL;
	return (tmp_path);
}

char	*find_no_builtin(char **good_path, char **command)
{
	char	**tmp_path;
	char	*result;
	int		i;

	if (!good_path || !command)
		return (NULL);
	tmp_path = build_command_paths(good_path, command[0]);
	if (!tmp_path)
		return (NULL);
	result = path_to_exc(tmp_path);
	i = 0;
	while (tmp_path[i])
	{
		if (tmp_path[i] != result)
			free(tmp_path[i]);
		i++;
	}
	free(tmp_path);
	return (result);
}
