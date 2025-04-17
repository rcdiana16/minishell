/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:26:18 by maximemarti       #+#    #+#             */
/*   Updated: 2025/04/16 00:47:14 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_initial_syntax(char **cmd, char **bad_token)
{
	if (!cmd[0])
		return (-1);
	if (ft_strncmp(cmd[0], ">>", 3) == 0)
	{
		if (bad_token)
			*bad_token = cmd[0];
		return (2);
	}
	if (ft_strncmp(cmd[0], "|", 2) == 0)
	{
		if (bad_token)
			*bad_token = cmd[0];
		return (0);
	}
	return (-1);
}

int	is_redirection(char *token)
{
	if (!token)
		return (0);
	return (ft_strncmp(token, ">", 1) == 0 || \
			ft_strncmp(token, ">>", 2) == 0 || \
			ft_strncmp(token, "<", 1) == 0 || \
			ft_strncmp(token, "<<", 2) == 0);
}

static int	check_pipe_error(char **cmd, int i, char **bad_token)
{
	if (i == 0 || !cmd[i - 1] || is_redirection(cmd[i - 1]))
	{
		if (bad_token)
			*bad_token = cmd[i];
		return (0);
	}
	/*if (!cmd[i + 1] || is_redirection(cmd[i + 1]) || (cmd[i + 1][0] == '|'))
	{
		if (bad_token)
		{
			if (cmd[i + 1])
				*bad_token = cmd[i + 1];
			else
				*bad_token = cmd[i];
		}
		return (0);
	}*/
	return (-1);
}

static int	check_redirection_error(char **cmd, int i, char **bad_token)
{
	if (!cmd[i + 1] || (cmd[i + 1][0] == '|') || is_redirection(cmd[i + 1]))
	{
		if (bad_token)
		{
			if (cmd[i + 1])
				*bad_token = cmd[i + 1];
		}
		return (0);
	}
	return (-1);
}

int	check_middle_syntax(char **cmd, char **bad_token)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '|')
		{
			if (check_pipe_error(cmd, i, bad_token) == 0)
				return (0);
		}
		else if (is_redirection(cmd[i]))
		{
			if (check_redirection_error(cmd, i, bad_token) == 0)
				return (0);
		}
		i++;
	}
	return (-1);
}


int	check_final_syntax(char **cmd, int i, char **bad_token)
{
	while (cmd[i])
	{
		if ((ft_strncmp(cmd[i], ">", 1) == 0 || \
			ft_strncmp(cmd[i], ">>", 2) == 0) && cmd[i + 1] == NULL)
		{
			if (bad_token)
				*bad_token = cmd[i];
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_syntax(char **cmd, char **bad_token)
{
	int	result;

	result = check_initial_syntax(cmd, bad_token);
	if (result != -1)
		return (result);
	result = check_middle_syntax(cmd, bad_token);
	if (result != -1)
		return (result);
	return (check_final_syntax(cmd, 0, bad_token));
}

