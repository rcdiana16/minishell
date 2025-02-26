/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/02/26 17:43:43 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		**path_splitted;
	t_command	*cmd_info;
	char		*ok;
	int			pid;
	int			i;
	char		*temp;

	*av = NULL;
	if (ac == 0)
		return (1);
	path_splitted = get_path();
	while (1)
	{
		cmd_info = get_input();
		if (!cmd_info || !cmd_info->tokens || !cmd_info->tokens[0])
		{
			free_command(cmd_info);
			continue ;
		}
		ok = ft_strjoin(path_splitted[4], "/");
		if (!ok)
		{
			free_command(cmd_info);
			continue ;
		}
		temp = ok;
		ok = ft_strjoin(ok, cmd_info->tokens[0]);
		free(temp);
		if (!ok)
		{
			free_command(cmd_info);
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(ok, cmd_info->tokens, env) == -1)
				perror("error ");
			i = 0;
			while (path_splitted[i])
			{
				free(path_splitted[i]);
				i++;
			}
			free(path_splitted);
			free(ok);
			free_command(cmd_info);
			exit(1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			free(ok);
			free_command(cmd_info);
		}
	}
	i = 0;
	while (path_splitted[i])
	{
		free(path_splitted[i]);
		i++;
	}
	free(path_splitted);
	return (0);
}
