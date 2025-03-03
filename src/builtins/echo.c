/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:32:03 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/03 22:44:32 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_echo(char **cmd, int i, int newline, t_env *env_mini)
{
	char	*expanded;

	while (cmd[i])
	{
		expanded = replace_env_vars(cmd[i], env_mini);
		write(1, expanded, strlen(expanded));
		free(expanded);
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void	ft_our_echo(char **cmd, t_env *env_mini)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!cmd || !cmd[0])
		return ;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (strncmp(cmd[1], "-n", strlen(cmd[1])) == 0)
	{
		newline = 0;
		i = 2;
	}
	print_echo(cmd, i, newline, env_mini);
}
