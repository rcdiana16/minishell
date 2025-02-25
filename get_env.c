/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:58:26 by cosmos            #+#    #+#             */
/*   Updated: 2025/02/25 14:13:07 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **env)
{
	char	**env_dup;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_dup = malloc(i * (sizeof(char *)));
	i = 0;
	while (env[i])
	{
		env_dup[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_dup);
}
