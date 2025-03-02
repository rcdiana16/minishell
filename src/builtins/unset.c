/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:58 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 16:18:47 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_env **env_mini, char *var)
{
	t_env *tmp = *env_mini;
	t_env *prev = NULL;

	while (tmp)
	{
		if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0 && ft_strlen(tmp->variable) == ft_strlen(var))
		{
			if (prev == NULL)
				*env_mini = tmp->next;
			else
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
