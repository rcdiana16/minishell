/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:32:03 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/01 21:32:18 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_our_echo(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	i = 1;
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
		i = 2;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) != 0)
		write(1, "\n", 1);
}
