/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 23:40:39 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_env *env_mini, char **cmd)
{
	t_env	*new_var;
	char	**tokens;

	if (!cmd || !cmd[1])
		return ;
	tokens = ft_split2(cmd[1], "=");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free(tokens);
		return ;
	}
	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		free(tokens);
		return ;
	}
	new_var->variable = ft_strdup(tokens[0]);
	new_var->value = ft_strdup(tokens[1]);
	new_var->next = NULL;
	free(tokens);
	while (env_mini->next)
		env_mini = env_mini->next;
	env_mini->next = new_var;
}
