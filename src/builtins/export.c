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

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	update_existing_variable(t_env *env_mini, char **tokens)
{
	while (env_mini)
	{
		if (strcmp(tokens[0], env_mini->variable) == 0)
		{
			free(env_mini->value);
			env_mini->value = strdup(tokens[1]);
			return (1);
		}
		env_mini = env_mini->next;
	}
	return (0);
}

void	add_new_variable(t_env *env_mini, char **tokens)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;

	new_var->variable = strdup(tokens[0]);
	new_var->value = strdup(tokens[1]);
	new_var->next = NULL;
	while (env_mini->next)
		env_mini = env_mini->next;

	env_mini->next = new_var;
}

void ft_export(t_env *env_mini, char **cmd)
{
	char	**tokens;

	if (!cmd || !cmd[1])
		return ;

	tokens = ft_split2(cmd[1], "=");
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_tokens(tokens);
		return ;
	}
	if (!update_existing_variable(env_mini, tokens))
		add_new_variable(env_mini, tokens);
	free_tokens(tokens);
}
