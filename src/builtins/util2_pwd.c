/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:12:43 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/02 15:36:47 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_concat(t_env *env, char *current_pwd, char *new_path)
{
	char	*temp;

	temp = ft_strjoin(current_pwd, "/");
	if (!temp)
		return ;
	free(env->value);
	env->value = ft_strjoin(temp, new_path);
	free(temp);
}

void	update_env_last_dir(t_env *env, char *new_path)
{
	char	*last_dir;

	last_dir = ft_strdup(ft_find_dir(new_path));
	if (!last_dir)
		return ;
	free(env->value);
	env->value = ft_strjoin(env->value, last_dir);
	free(last_dir);
}

void	update_env_direct(t_env *env, char *new_path, int flag)
{
	free(env->value);
	if (flag == 3)
		env->value = ft_strdup(new_path);
	else if (flag == 4)
		env->value = ft_strdup(ft_find_gd_dir(new_path));
}
