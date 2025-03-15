/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:13:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/15 19:13:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_existing_variable(t_env *env_mini, char **cmd, char **tokens)
{
	char	*value;

	free(env_mini->value);
	if (tokens[1])
		value = ft_strdup(tokens[1]);
	else
		value = ft_strdup("");
	free_arr(tokens);
	join_cmd_values(cmd, &value);
	delete_quotes(value);
	env_mini->value = value;
	return (1);
}

int	update_existing_variable(t_env *env_mini, char **cmd)
{
	char	**tokens;

	if (!cmd || !cmd[1])
		return (0);
	tokens = ft_split2(cmd[1], "=");
	if (!tokens || !tokens[0])
		return (0);
	while (env_mini)
	{
		if (ft_strncmp(tokens[0], env_mini->variable, \
			ft_strlen(tokens[0])) == 0)
			return (handle_existing_variable(env_mini, cmd, tokens));
		env_mini = env_mini->next;
	}
	free_arr(tokens);
	return (0);
}
