/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:58:26 by cosmos            #+#    #+#             */
/*   Updated: 2025/02/25 22:10:16 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var, char **env)
{
	int		i;
	int		var_len;
	char	*variable;

	i = 0;
	var_len = ft_strlen(var);
	if (env == NULL || *env == NULL || var == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
		{
			variable = &env[i][var_len + 1];
			return (variable);
		}
		i++;
	}
	return (NULL);
}
