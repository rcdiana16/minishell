/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:03:53 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/21 19:13:44 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*clean_space(char *token)
{
	int		j;
	int		k;
	int		space_found;
	char	*cleaned_token;

	j = 0;
	k = 0;
	space_found = 0;
	cleaned_token = malloc(strlen(token) + 1);
	if (!cleaned_token)
		return (NULL);
	while (token[j])
	{
		if (token[j] != ' ')
		{
			cleaned_token[k++] = token[j];
			space_found = 0;
		}
		else if (!space_found)
		{
			cleaned_token[k++] = ' ';
			space_found = 1;
		}
		j++;
	}
	cleaned_token[k] = '\0';
	return (cleaned_token);
}

void	init_new_variable(t_env **new_var, char **tokens)
{
	char	*cleaned_value;

	*new_var = malloc(sizeof(t_env));
	if (!*new_var)
		return ;
	(*new_var)->variable = ft_strdup(tokens[0]);
	if (tokens[1])
	{
		cleaned_value = clean_space(tokens[1]);
		(*new_var)->value = ft_strdup(cleaned_value);
		free(cleaned_value);
	}
	else
		(*new_var)->value = ft_strdup("");
	free_arr(tokens);
}

/*
void	init_new_variable(t_env **new_var, char **tokens)
{
	*new_var = malloc(sizeof(t_env));
	if (!*new_var)
		return ;
	(*new_var)->variable = ft_strdup(tokens[0]);
	if (tokens[1])
		(*new_var)->value = ft_strdup(clean_space(tokens[1]));
	else
		(*new_var)->value = ft_strdup("");
	free_arr(tokens);
}*/

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
		tokens = ft_split(cmd[1], '=');
	else
		tokens = ft_split(cmd[2], ' ');
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
