/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 16:07:03 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_flag_1(t_env *env, char *current_pwd, char *new_path)
{
	env->value = ft_strjoin(current_pwd, "/");
	env->value = ft_strjoin(env->value, new_path);
}

void	handle_flag_0(t_env *env, char *new_path)
{
	char	*last_dir;

	last_dir = ft_strdup(ft_find_dir(new_path));
	env->value = ft_strjoin(env->value, last_dir);
	free(last_dir);
}

void	handle_flag_3(t_env *env, char *new_path)
{
	env->value = ft_strdup(new_path);
}

void	handle_flag_4(t_env *env, char *new_path)
{
	env->value = ft_strdup(ft_find_gd_dir(new_path));
}

void	update_env(t_env *env, char *new_path, char *env_to_update, int flag)
{
	char	*current_pwd;

	current_pwd = get_env_value(env, env_to_update);
	while (env)
	{
		if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0)
		{
			if (flag == 1)
				handle_flag_1(env, current_pwd, new_path);
			else if (flag == 0)
				handle_flag_0(env, new_path);
			else if (flag == 3)
				handle_flag_3(env, new_path);
			else if (flag == 4)
				handle_flag_4(env, new_path);
			return ;
		}
		env = env->next;
	}
}
