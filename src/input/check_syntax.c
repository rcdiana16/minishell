/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:26:18 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 17:27:27 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_initial_syntax(char **cmd)
{
	if (ft_strncmp(cmd[0], ">>", 4) == 0)
		return (2);
	if (ft_strncmp(cmd[0], "|", 1) == 0)
		return (0);
	return (-1);
}

int	check_middle_syntax(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if (ft_strncmp(cmd[i], ">", 1) == 0 && \
		ft_strncmp(cmd[i + 1], ">", 1) == 0)
			return (0);
		if (ft_strncmp(cmd[i], ">>", 2) == 0 && \
		ft_strncmp(cmd[i + 1], ">>", 2) == 0)
			return (0);
		if (ft_strncmp(cmd[i], ">", 1) == 0 && \
		ft_strncmp(cmd[i + 1], "|", 1) == 0)
			return (0);
		if (ft_strncmp(cmd[i], ">>", 2) == 0 && \
		ft_strncmp(cmd[i + 1], "|", 1) == 0)
			return (0);
		if (ft_strncmp(cmd[i], "|", 1) == 0 && \
		ft_strncmp(cmd[i + 1], "|", 1) == 0)
			return (0);
		i++;
	}
	return (-1);
}

int	check_final_syntax(char **cmd, int i)
{
	if ((ft_strncmp(cmd[i], ">", 1) == 0 || \
	ft_strncmp(cmd[i], ">>", 2) == 0) && cmd[i + 1] == NULL)
		return (0);
	return (1);
}

int	check_syntax(char **cmd)
{
	int	result;

	result = check_initial_syntax(cmd);
	if (result != -1)
		return (result);
	result = check_middle_syntax(cmd);
	if (result != -1)
		return (result);
	return (check_final_syntax(cmd, 0));
}
