/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 23:03:24 by diana            ###   ########.fr       */
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
	current_pwd = get_env_value(env, "pwd");
	while (oldpwd_entry)
	{
		if (ft_strncmp(oldpwd_entry->variable, "oldpwd", 6) == 0)
		{
			free(oldpwd_entry->value);
			if (current_pwd)
				oldpwd_entry->value = ft_strdup(current_pwd);
			else
				oldpwd_entry->value = NULL;
		}
		if (ft_strncmp(oldpwd_entry->variable, "pwd", 3) == 0)
		{
			free(oldpwd_entry->value);
			oldpwd_entry->value = ft_strdup(new_path);
			return;
		}
		oldpwd_entry = oldpwd_entry->next;
	}

	oldpwd_entry = malloc(sizeof(t_env));
	oldpwd_entry->variable = ft_strdup("pwd");
	oldpwd_entry->value = ft_strdup(new_path);
	oldpwd_entry->next = env;
	env = oldpwd_entry;
}
