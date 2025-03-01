/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:36:55 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 22:59:02 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_path(char *path)
{
	if (path == NULL)
		return (0);
	if (path[0] == '/')
	{
		if (chdir(path) == 0)
		{
			chdir("/");
			return (1);
		}
	}
	else
	{
		if (chdir(path) == 0)
		{
			chdir("/");
			return (1);
		}
	}
	return (0);
}

