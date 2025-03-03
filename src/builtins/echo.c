/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:32:03 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/03 15:53:44 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_env_var_echo(char *cmd, t_env *env_mini)
{
	char	*value;

	cmd = cmd + 1;
	value = get_env_value(env_mini, cmd);
	if (value != NULL)
		printf("%s\n", value);
	else
		printf("\n");
}

void	print_echo(char **cmd, int i, int newline)
{
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
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

	if (!cmd || !cmd[0])
		return ;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	i = 1;
	newline = 1;
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
	{
		newline = 0;
		i = 2;
	}
	if (ft_strncmp(cmd[1], "$", 1) == 0)
	{
		handle_env_var_echo(cmd[1], env_mini);
		return ;
	}
	print_echo(cmd, i, newline);
}
