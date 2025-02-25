/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:58:26 by cosmos            #+#    #+#             */
/*   Updated: 2025/02/25 19:07:09 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var, char **env)
{
	int		i;
	int		var_len;
	char	*value_start;

	i = 0;
	var_len = ft_strlen(var);
	if (env == NULL || *env == NULL || var == NULL)
		return NULL;

	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
		{
			value_start = &env[i][var_len + 1];
			return (value_start);
		}
		i++;
	}
	return (NULL);
}
