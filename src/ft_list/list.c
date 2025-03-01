/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:08:20 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/01 17:23:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_node(char *var, char *val)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->variable = ft_strdup(var);
	new_node->value = ft_strdup(val);
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_env **head, char *var, char *val)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_node(var, val);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	get_list_env(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*equal_sign;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			append_node(&env_list, envp[i], equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
}
