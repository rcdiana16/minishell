/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/15 19:18:29 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_quoted_values(char **cmd, char **value)
{
	int		i;
	char	*temp;

	i = 2;
	while (cmd[i])
	{
		temp = ft_strjoin(*value, " ");
		free(*value);
		*value = ft_strjoin(temp, cmd[i]);
		free(temp);
		i++;
	}
}

void	assign_value(char **cmd, char **value)
{
	free(*value);
	if (cmd[1][ft_strlen(cmd[1]) - 1] == '=')
		*value = ft_strdup(cmd[2]);
	else
		*value = ft_strdup(ft_strrchr(cmd[1], '=') + 1);
}

void	add_new_variable(t_env *env_mini, char **cmd)
{
	t_env	*new_var;
	char	**tokens;

	if (!cmd || !cmd[1])
		return ;
	tokens = ft_split2(cmd[1], "=");
	if (!tokens || !tokens[0])
		return ;
	init_new_variable(&new_var, tokens);
	join_cmd_values(cmd, &new_var->value);
	delete_quotes(new_var->value);
	new_var->next = NULL;
	while (env_mini->next)
		env_mini = env_mini->next;
	env_mini->next = new_var;
}

static int	is_invalid_identifier(char **tokens)
{
	if (!tokens || !tokens[0] || !is_valid_variable_name(tokens[0]))
	{
		write(2, "export: ", 8);
		if (tokens && tokens[0])
			write(2, tokens[0], ft_strlen(tokens[0]));
		write(2, ": not a valid identifier\n", 25);
		set_gcode(EXIT_FAILURE);
		free_arr(tokens);
		return (1);
	}
	return (0);
}

void	ft_export(t_env *env_mini, char **cmd)
{
	char	**tokens;

	if (!cmd || !cmd[1])
		return ;
	tokens = get_tokens(cmd);
	if (is_invalid_identifier(tokens))
		return ;
	if (!update_existing_variable(env_mini, cmd))
		add_new_variable(env_mini, cmd);
	free_arr(tokens);
}
