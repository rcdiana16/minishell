/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:03:53 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/14 23:04:13 by cosmos           ###   ########.fr       */
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
