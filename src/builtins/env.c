/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:20:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/10 20:48:25 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_our_env(t_env *env_mini)
{
	while (env_mini)
	{
		ft_printf("%s=%s\n", env_mini->variable, env_mini->value);
		env_mini = env_mini->next;
	}
	set_gcode(EXIT_SUCCESS);
}
