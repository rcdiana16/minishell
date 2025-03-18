/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:22:54 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/18 11:26:35 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_special_var(t_cmd_state *state, char *result, int j)
{
	j = process_exit_code(result, j, state->cmd_info);
	state->i++;
	return (j);
}

static int	process_env_var_internal(t_cmd_state *state, char *result, \
	int j, t_env *env_mini)
{
	return (process_env_var(state, result, j, env_mini));
}

int	process_var(t_cmd_state *state, char *result, int j, t_env *env_mini)
{
	state->i++;
	if (state->cmd[state->i] == '?')
		return (handle_special_var(state, result, j));
	return (process_env_var_internal(state, result, j, env_mini));
}
