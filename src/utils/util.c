/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:46 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/03 15:49:08 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(t_env *env_mini, const char *var)
{
	if (var != NULL)
	{
		while (env_mini != NULL)
		{
			if ((ft_strncmp(env_mini->variable, var, \
				ft_strlen(env_mini->variable))) == 0)
				return (env_mini->value);
			env_mini = env_mini->next;
		}
	}
	return (NULL);
}
