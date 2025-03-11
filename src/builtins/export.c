/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/11 11:04:52 by cosmos           ###   ########.fr       */
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
	if (!tokens || !tokens[1])
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

	if (!tokens || !tokens[1])
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
	int		i;

	i = 0;
	if (!cmd || !cmd[1])
		return ;
	tokens = ft_split2(cmd[1], "=");
	if (!tokens || !tokens[0])
		return ;
	while (tokens[0][i])
	{
		if (ft_isalpha(tokens[0][i]) != 1)
		{
			write(2, "export: ", ft_strlen("export: "));
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, ": not a valid identifier\n", \
			ft_strlen(": not a valid identifier\n"));
			//set_gcode(EXIT_FAILURE);
			//printf("g_code = %d\n", get_gcode());
			return ;
		}
		i++;
	}
	if (!update_existing_variable(env_mini, tokens))
		add_new_variable(env_mini, tokens);
	free_tokens(tokens);
}
