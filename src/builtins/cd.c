/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 23:27:17 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_path(char *path, t_env *env_mini)
{
	if (path == NULL)
		return (0);
	if (chdir(path) == 0)
	{
		chdir(path);
		update_env(env_mini, path);
		return (1);
	}
	else
		perror("Error: ");
	return (0);
}
