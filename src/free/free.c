/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:24:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/08 14:54:12 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_command(t_command *cmd_info)
{
	int	i;

	if (!cmd_info)
		return ;
	if (cmd_info->tokens)
	{
		i = 0;
		while (cmd_info->tokens[i])
		{
			free(cmd_info->tokens[i]);
			i++;
		}
		free(cmd_info->tokens);
	}
	free(cmd_info);
}

void	free_arr(char **tok)
{
	int	i;

	i = 0;
	if (!tok)
		return ;
	while (tok[i])
	{
		free(tok[i]);
		i++;
	}
	free(tok);
}

void	free_node(t_env *node)
{
	if (!node)
		return ;
	free(node->variable);
	free(node->value);
	free(node);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free_node(tmp);
	}
}
