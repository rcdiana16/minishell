/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:03:26 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/11 16:34:30 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*initialize_environment(char **env, t_env *env_list)
{
	return (get_list_env(env, env_list));
}

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
	strcpy(entry, variable);
	entry[var_len] = '=';
	strcpy(entry + var_len + 1, value);
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
	return (env_array);
}

char	**convert_env_to_array(t_env *env)
{
	int		size;
	char	**env_array;
	int		i;

	size = env_list_size(env);
	env_array = allocate_env_array(size);
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		env_array[i] = allocate_env_entry(env->variable, env->value);
		if (!env_array[i])
		{
			while (i-- > 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
