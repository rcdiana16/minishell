/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 16:40:29 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_env **env_mini, char *var, char *value)
{
	t_env	*tmp;
	t_env	*new_var;

	tmp = *env_mini;
	new_var = malloc(sizeof(t_env));
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0 && \
		ft_strlen(tmp->variable) == ft_strlen(var))
		{
			free (tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	if (!new_var)
		return ;
	new_var->variable = ft_strdup(var);
	new_var->value = ft_strdup(value);
	new_var->next = *env_mini;
	*env_mini = new_var;
}
