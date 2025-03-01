/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 18:06:46 by diana            ###   ########.fr       */
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

int	check_builtins(char **command)
{
	if ((ft_strncmp(command[0], "echo", ft_strlen(command[0]))) == 0)
		return (ft_our_echo(command), 1);
	else if ((ft_strncmp(command[0], "cd", ft_strlen(command[0]))) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	//else if ((ft_strncmp(command[0], "pwd", ft_strlen(command[0]))) == 0)
		//return (ft_our_pwd(env), 1);
	else if ((ft_strncmp(command[0], "export", ft_strlen(command[0]))) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	else if ((ft_strncmp(command[0], "unset", ft_strlen(command[0]))) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	else if ((ft_strncmp(command[0], "env", ft_strlen(command[0]))) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	else
		return (0);
}
