/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:03:53 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/15 19:17:39 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_new_variable(t_env **new_var, char **tokens)
{
	*new_var = malloc(sizeof(t_env));
	if (!*new_var)
		return ;
	(*new_var)->variable = ft_strdup(tokens[0]);
	if (tokens[1])
		(*new_var)->value = ft_strdup(tokens[1]);
	else
		(*new_var)->value = ft_strdup("");
	free_arr(tokens);
}

int	is_valid_variable_name(char *name)
{
	int	i;

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

char	**get_tokens(char **cmd)
{
	char	**tokens;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	i--;
	if (i == 1)
		tokens = ft_split2(cmd[1], "=");
	else
		tokens = ft_split2(cmd[2], " ");
	return (tokens);
}

void	join_cmd_values(char **cmd, char **value)
{
	if (!cmd || !cmd[1])
		return ;
	if (cmd[1][0] == '\"' || cmd[1][0] == '\'')
		join_quoted_values(cmd, value);
	else if (cmd[2])
		assign_value(cmd, value);
}
