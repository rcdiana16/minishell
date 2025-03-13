/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/13 13:54:34 by cosmos           ###   ########.fr       */
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

void	handle_flag_0(t_env *env, char *new_path)
{
	char	*last_dir;

	if (!new_path)
		return ;
	last_dir = ft_strdup(ft_find_dir(new_path));
	if (!last_dir)
		return ;
	env->value = ft_strjoin(env->value, last_dir);
	free(last_dir);
}

void	handle_flag_3(t_env *env, char *new_path)
{
	if (!env || !new_path)
		return ;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(new_path);
}

void	handle_flag_4(t_env *env, char *new_path)
{
	if (!new_path)
		return ;
	env->value = ft_strdup(ft_find_gd_dir(new_path));
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
			//else if (flag == 0)
				//handle_flag_0(env, new_path);
			else if (flag == 3)
				handle_flag_3(env, new_path);
			//else if (flag == 4)
				//handle_flag_4(env, new_path);
			return ;
		}
		env = env->next;
	}
}
