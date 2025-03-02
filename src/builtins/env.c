/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:20:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/02 11:39:16 by maximemarti      ###   ########.fr       */
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
}
