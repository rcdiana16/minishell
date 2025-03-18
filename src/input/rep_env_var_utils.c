/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:22:54 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/18 17:27:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_special_var(t_cmd_state *state, char *result, \
	int j, t_shell *shell)
{
	j = process_exit_code(result, j, shell);
	state->i++;
	return (j);
}

static int	process_env_var_internal(t_cmd_state *state, char *result, \
	int j, t_env *env_mini)
{
	return (process_env_var(state, result, j, env_mini));
}

int	process_var(t_cmd_state *state, char *result, int j, t_shell_env *shell_env)
{
	state->i++;
	if (state->cmd[state->i] == '?')
		return (handle_special_var(state, result, j, shell_env->shell));
	return (process_env_var_internal(state, result, j, shell_env->env_mini));
}
