/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ex_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:30 by diana             #+#    #+#             */
/*   Updated: 2025/02/26 18:47:37 by diana            ###   ########.fr       */
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
	i = 0;
	while (path_splited[i])
	{
		good_path[i] = ft_strjoin(path_splited[i], "/");
		if (!good_path)
			return (NULL);
		i++;
	}
	i = 0;
	while (good_path[i])
	{
		printf("%s\n", good_path[i]);
		i++;
	}
	return (good_path);
}
