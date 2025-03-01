/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 18:45:18 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_our_strcmp(const char *s1, const char *s2)
{
	return	ft_strncmp(s1, s2, INT_MAX);
}

t_env	*find_env_var(t_env *env, const char *var, int (*cmp)(const char *, const char *))
{
	while (env)
	{
		if (cmp(env->variable, var) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}

char	*get_env_value(t_env *env, const char *var)
{
	t_env	*entry;
	
	entry = find_env_var(env, var, ft_our_strcmp);
	return (entry ? entry->value : NULL);
}

void	ft_our_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_env_value(env, "pwd");
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("pwd: no such variable");
}
