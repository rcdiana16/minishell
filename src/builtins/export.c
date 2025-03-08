/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/08 17:54:18 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	update_existing_variable(t_env *env_mini, char **tokens)
{
	if (!tokens)
		return (0);
	while (env_mini)
	{
		if (ft_strncmp(tokens[0], env_mini->variable, \
			ft_strlen(tokens[0])) == 0)
		{
			free(env_mini->value);
			env_mini->value = ft_strdup(tokens[1]);
			return (1);
		}
		env_mini = env_mini->next;
	}
	return (0);
}

void	add_new_variable(t_env *env_mini, char **tokens)
{
	t_env	*new_var;

	if (!tokens)
		return ;
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->variable = ft_strdup(tokens[0]);
	new_var->value = ft_strdup(tokens[1]);
	new_var->next = NULL;
	while (env_mini->next)
		env_mini = env_mini->next;
	env_mini->next = new_var;
}

void	ft_export(t_env *env_mini, char **cmd)
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
