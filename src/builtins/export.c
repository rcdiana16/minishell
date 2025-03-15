/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/03/14 23:48:49 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_existing_variable(t_env *env_mini, char **cmd, char **tokens)
{
	char	*value;
	char	*temp;
	int		i;

	free(env_mini->value);
	if (tokens[1])
		value = ft_strdup(tokens[1]);
	else
		value = ft_strdup("");
	free_arr(tokens);
	i = 2;
	while (cmd[i])
	{
		temp = ft_strjoin(value, " ");
		free(value);
		value = ft_strjoin(temp, cmd[i]);
		free(temp);
		i++;
	}
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

void	join_cmd_values(char **cmd, char **value)
{
	int		i;
	char	*temp;

	i = 2;
	if ((*value)[0] == '\"' || (*value)[0] == '\'')
	{
		while (cmd[i])
		{
			temp = ft_strjoin(*value, " ");
			free(*value);
			*value = ft_strjoin(temp, cmd[i]);
			free(temp);
			i++;
		}
	}
	else
	{
		if (cmd[2])
    {
      free(*value);
      *value = ft_strdup(cmd[1]);
    }
	}
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

int is_valid_variable_name(char *name)
{
    int i;

    if (name == NULL || name[0] == '\0')
        return (0);
    if (!(ft_isalpha(name[0]) || name[0] == '_'))
        return (0);
    i = 1;
    while (name[i])
    {
        if (!(ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

void	ft_export(t_env *env_mini, char **cmd)
{
	char	**tokens;

	if (!cmd || !cmd[1])
    return ;
  tokens = ft_split2(cmd[1], "=");
	if (!tokens || !tokens[0])
		return ;
	if (!is_valid_variable_name(tokens[0]))
    {
        write(2, "export: ", 8);
        write(2, tokens[0], ft_strlen(tokens[0]));
        write(2, ": not a valid identifier\n", 25);
        set_gcode(EXIT_FAILURE);
        free_arr(tokens);
        return;
    }
	if (!update_existing_variable(env_mini, cmd))
		add_new_variable(env_mini, cmd);
	free_arr(tokens);
}
