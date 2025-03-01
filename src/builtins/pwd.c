/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 23:43:03 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(t_env *env_mini, const char *var)
{
	while (env_mini != NULL)
	{
		if ((ft_strncmp(env_mini->variable, var, ft_strlen(var))) == 0)
			return (env_mini->value);
		env_mini = env_mini->next;
	}
	return (NULL);
}

void	ft_our_pwd(t_env *env_mini)
{
	char	*pwd;

	pwd = get_env_value(env_mini, "PWD");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("pwd: no such variable");
}

void	update_env(t_env *env, char *new_path)
{
	t_env	*oldpwd_entry;
	char	*current_pwd;

	oldpwd_entry = env;
	current_pwd = get_env_value(env, "PWD");
	while (env)
	{
		
		if (ft_strncmp(env->variable, "PWD", 3) == 0)
		{
			env->value = ft_strjoin(current_pwd, "/");
			env->value = ft_strjoin(env->value, new_path);
			return ;
		}
		env = env->next;
	}
	oldpwd_entry = malloc(sizeof(t_env));
	oldpwd_entry->variable = ft_strdup("PWD");
	oldpwd_entry->value = ft_strdup(new_path);
	oldpwd_entry->next = env;
	env = oldpwd_entry;
}
