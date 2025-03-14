/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:08:21 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 12:18:37 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_exit_code(char *result, int j)
{
	char	*var_value;
	char	*tmp;

	var_value = ft_itoa(g_code);
	tmp = var_value;
	while (*tmp)
		result[j++] = *tmp++;
	free(var_value);
	return (j);
}

char	*get_env_value(t_env *env_mini, const char *var)
{
	if (var != NULL)
	{
		while (env_mini != NULL)
		{
			if ((ft_strncmp(env_mini->variable, var, \
				ft_strlen(var) + 1)) == 0)
				return (env_mini->value);
			env_mini = env_mini->next;
		}
	}
	return (NULL);
}

int	get_gcode(void)
{
	return (g_code);
}

void	set_gcode(int val)
{
	g_code = val;
}
