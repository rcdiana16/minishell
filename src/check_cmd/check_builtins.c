/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:38:03 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 23:31:29 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtins(char **command, t_env *env_mini)
{
	if ((ft_strncmp(command[0], "echo", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_echo(command), 1);
	else if ((ft_strncmp(command[0], "cd", ft_strlen(command[0]) + 1)) == 0)
		return (is_valid_path(command[1], env_mini), 1);
	else if ((ft_strncmp(command[0], "pwd", ft_strlen(command[0]) + 1)) == 0)
		return (ft_our_pwd(env_mini), 1);
	else if ((ft_strncmp(command[0], "export", ft_strlen(command[0]) + 1)) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	else if ((ft_strncmp(command[0], "unset", ft_strlen(command[0]) + 1)) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	else if ((ft_strncmp(command[0], "env", ft_strlen(command[0]) + 1)) == 0)
		return ((printf("Ok %s\n", command[0])), 1);
	else if ((ft_strncmp(command[0], "exit", ft_strlen(command[0]) + 1)) == 0)
		exit (0);
	else
		return (0);
}
