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

void	ft_unset(t_env *env_mini, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env_mini;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0 && \
		ft_strlen(tmp->variable) == ft_strlen(var))
		{
			if (prev == NULL)
				env_mini = tmp->next;
			else
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
