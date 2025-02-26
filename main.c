/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/02/26 17:12:57 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**path_splitted;
	char	**commande;
	char	*ok;
	int		pid;
	int		i;
	char	*temp;

	*av = NULL;
	if (ac == 0)
		return (1);
	path_splitted = get_path();
	while (1)
	{
		commande = get_input();
		ok = ft_strjoin(path_splitted[4], "/");
		if (!ok)
			continue ;
		temp = ok;
		ok = ft_strjoin(ok, commande[0]);
		free(temp);
		if (!ok)
			continue ;
		pid = fork();
		if (pid == 0)
		{
			if (execve(ok, commande, env) == -1)
				perror("error ");
			i = 0;
			while (path_splitted[i])
			{
				free(path_splitted[i]);
				i++;
			}
			free(path_splitted);
			i = 0;
			while (commande[i])
			{
				free(commande[i]);
				i++;
			}
			free(commande);
			free(ok);
			exit(1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			free(ok);
			i = 0;
			while (commande[i])
			{
				free(commande[i]);
				i++;
			}
			free(commande);
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
