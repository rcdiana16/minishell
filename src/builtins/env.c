/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:20:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/08 17:14:53 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_our_env(t_env *env_mini)
{
	while (env_mini)
	{
		printf("%s=%s\n", env_mini->variable, env_mini->value);
		env_mini = env_mini->next;
	}
	set_gcode(EXIT_SUCCESS);
}
