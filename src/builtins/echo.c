/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:32:03 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/08 17:10:25 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_echo(char **cmd, int i, int newline)
{
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline != 0)
		write(1, "\n", 1);
}

void	ft_our_echo(char **cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		newline = 0;
		i = 2;
	}
	print_echo(cmd, i, newline);
}
