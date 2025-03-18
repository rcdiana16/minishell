/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:46 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/18 17:28:06 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_var_name(t_cmd_state *state)
{
	int		k;
	int		j;
	char	*var_name;

	k = 0;
	j = 0;
	while (state->cmd[state->i] && (ft_isalnum(state->cmd[state->i]) \
	|| state->cmd[state->i] == '_'))
	{
		k++;
		(state->i)++;
	}
	if (k == 0)
		return (NULL);
	var_name = malloc(sizeof(char) * (k + 1));
	if (!var_name)
		return (NULL);
	while (j < k)
	{
		var_name[j] = state->cmd[state->i - k + j];
		j++;
	}
	var_name[k] = '\0';
	return (var_name);
}

int	process_env_var(t_cmd_state *state, char *result, int j, t_env *env_mini)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = extract_var_name(state);
	if (var_name)
	{
		var_value = get_env_value(env_mini, var_name);
		if (!var_value)
			var_value = "";
		tmp = var_value;
		while (*tmp)
			result[j++] = *tmp++;
		free(var_name);
	}
	return (j);
}

int	copy_non_var_part(t_cmd_state *state, char *result, int j)
{
	result[j++] = state->cmd[state->i];
	(state->i)++;
	return (j);
}

char	*replace_env_vars(char *cmd, t_env *env_mini, t_shell *shell)
{
	int			i;
	int			j;
	char		*result;
	t_cmd_state	state;
	t_shell_env	shell_env;

	i = 0;
	j = 0;
	result = malloc(256);
	if (!result)
		return (NULL);
	state.cmd = cmd;
	state.i = i;
	shell_env.env_mini = env_mini;
	shell_env.shell = shell;
	while (state.cmd[state.i])
	{
		if (state.cmd[state.i] == '$' && state.cmd[state.i + 1])
			j = process_var(&state, result, j, &shell_env);
		else
			j = copy_non_var_part(&state, result, j);
	}
	result[j] = '\0';
	return (result);
}
