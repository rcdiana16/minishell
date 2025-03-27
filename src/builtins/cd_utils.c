/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:02:56 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 11:03:32 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_flag_1(t_env *env, char *new_path)
{
	if (!env || !new_path)
		return ;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(new_path);
	if (!env->value)
		return ;
}

void	handle_flag_3(t_env *env, char *new_path)
{
	if (!env || !new_path)
		return ;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(new_path);
}

void	update_env(t_env *env, char *new_path, char *env_to_update, int flag)
{
	char	*current_pwd;

	if (!new_path | ! env_to_update)
		return ;
	current_pwd = get_env_value(env, env_to_update);
	if (!current_pwd)
		return ;
	while (env)
	{
		if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0)
		{
			if (flag == 1)
				handle_flag_1(env, new_path);
			else if (flag == 3)
				handle_flag_3(env, new_path);
			return ;
		}
		env = env->next;
	}
}
