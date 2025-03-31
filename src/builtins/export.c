/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/18 10:16:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_quoted_values(char **cmd, char **value)
{
	int		i;
	char	*temp;

	i = 0;
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
	char *tmp;

	tmp = ft_strdup(cmd[1]);
	*value = tmp;
	free(tmp);
}

void	add_new_variable(t_env *env_mini, char **tokens, t_env *new_var)
{
	if (!tokens || !tokens[0])
		return ;
	join_cmd_values(tokens, &new_var->value);
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
		free_arr(tokens);
		return (1);
	}
	if (!tokens[1])
	{
		free_arr(tokens);
		return (1);
	}
	return (0);
}

int	ft_export(t_env *env_mini, char **cmd)
{
	char	**tokens;
	int		i;
	t_env	*new_var;

	i = 1;
	if (!cmd || !cmd[1])
		return (1);
	while (cmd[i])
	{
		tokens = get_tokens(cmd[i]);
		if (is_invalid_identifier(tokens))
			return (1);
		if (!update_existing_variable(env_mini, tokens))
		{
			new_var = malloc(sizeof(t_env));
			if (!new_var)
				return (1);
			init_new_variable(new_var, tokens);
			add_new_variable(env_mini, tokens, new_var);
		}
		free_arr(tokens);
		i++;
	}
	return (0);
}
