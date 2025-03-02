/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:58 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 16:39:36 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	remove_first_node(t_env *env_mini, char *var)
{
	t_env	*tmp;

	if (env_mini && strcmp((env_mini)->variable, var) == 0)
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
		if (strcmp(tmp->variable, var) == 0)
		{
			prev->next = tmp->next;
			free(tmp->variable);
			free(tmp->value);
			free(tmp);
			return;
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
