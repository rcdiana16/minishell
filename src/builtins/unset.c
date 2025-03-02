/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:58 by diana             #+#    #+#             */
/*   Updated: 2025/03/03 00:33:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	remove_first_node(t_env *env_mini, char *var)
{
	t_env	*tmp;

	if (env_mini && ft_strncmp((env_mini)->variable, var, ft_strlen(var)) == 0)
	{
		tmp = env_mini;
		env_mini = tmp->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

void	remove_variable(t_env *env_mini, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env_mini;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0)
		{
			prev->next = tmp->next;
			free(tmp->variable);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_env *env_mini, char **cmd)
{
	if (!cmd || !cmd[1])
		return ;
	if (remove_first_node(env_mini, cmd[1]))
		return ;
	remove_variable(env_mini, cmd[1]);
}
