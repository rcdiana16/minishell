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
/*
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
}*/

void	print_echo(char **cmd, int i, int newline)
{
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i])); // this will print nothing for ""
		if (cmd[i + 1] != NULL)
			write(1, " ", 1); // this still writes a space
		i++;
	}
	if (newline != 0)
		write(1, "\n", 1);
}


int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
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
	if (ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		int j = 1;
		while(ft_strncmp(cmd[j], "-n", 3) == 0)
			j++;
		newline = 0;
		i = j;
	}
	print_echo(cmd, i, newline);
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

	if (is_n_flag(cmd[1]))
	{
		int j = 1;
		while (cmd[j] && is_n_flag(cmd[j]))
			j++;
		newline = 0;
		i = j;
	}

	print_echo(cmd, i, newline);goog
}*/
void	ft_our_echo(char **cmd)
{
	int	i = 1;
	int	newline = 1;

	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}

	// only parse flags if they come immediately at the beginning
	while (cmd[i] && is_n_flag(cmd[i]))
	{
		newline = 0;
		i++;
	}

	print_echo(cmd, i, newline);
}


