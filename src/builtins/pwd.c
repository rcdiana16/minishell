/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:14:50 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 12:22:44 by maximemarti      ###   ########.fr       */
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

char	*ft_find_dir(char *path)
{
	int	i;
	int	c_slash;

	c_slash = 0;
	i = ft_strlen(path) - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			c_slash = i;
			break ;
		}
		i--;
	}
	return (path + c_slash);
}

char	*ft_find_gd_dir(char *path)
{
	int		i;
	int		c_slash;
	char	*good_path;

	i = ft_strlen(path) - 1;
	c_slash = 0;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			c_slash = i;
			break ;
		}
		i--;
	}
	good_path = ft_strndup(path, c_slash);
	return (good_path);
}

void	update_env(t_env *env, char *new_path, char *env_to_update, int flag)
{
	char	*current_pwd;
	char	*last_dir;

	current_pwd = get_env_value(env, env_to_update);
	while (env)
	{
		if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0 && flag == 1)
		{
			env->value = ft_strjoin(current_pwd, "/");
			env->value = ft_strjoin(env->value, new_path);
			return ;
		}
		else if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0 && flag == 0)
		{
			last_dir = ft_strdup(ft_find_dir(new_path));
			env->value = ft_strjoin(env->value, last_dir);
			return ;
		}
		else if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0 && flag == 3)
		{
			env->value = ft_strdup(new_path);
			return ;
		}
		else if (ft_strncmp(env->variable, env_to_update, \
			ft_strlen(env->variable)) == 0 && flag == 4)
		{
			env->value = ft_strdup(ft_find_gd_dir(new_path));
			return ;
		}
		env = env->next;
	}
}
