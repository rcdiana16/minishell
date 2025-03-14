/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:08 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 11:45:25 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	*allocate_env_entry(const char *variable, const char *value)
{
	size_t	var_len;
	size_t	val_len;
	size_t	total_len;
	char	*entry;

	var_len = ft_strlen(variable);
	val_len = ft_strlen(value);
	total_len = var_len + val_len + 2;
	entry = malloc(total_len);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, variable, ft_strlen(variable));
	entry[var_len] = '=';
	ft_strlcpy(entry + var_len + 1, value, ft_strlen(value));
	return (entry);
}

char	**allocate_env_array(int size)
{
	char	**env_array;

	env_array = malloc((size + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	env_array[size] = NULL;
	return (env_array);
}

char	**convert_env_to_array(t_env *env_mini)
{
	int		size;
	char	**env_array;
	int		i;

	size = env_list_size(env_mini);
	env_array = allocate_env_array(size);
	if (!env_array)
		return (NULL);
	i = 0;
	while (env_mini)
	{
		env_array[i] = allocate_env_entry(env_mini->variable, env_mini->value);
		if (!env_array[i])
		{
			while (i-- > 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		env_mini = env_mini->next;
		i++;
	}
	env_array[i] = NULL;
	free_env_list(env_mini);
	return (env_array);
}
