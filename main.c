/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/02/25 22:52:40 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**path_splitted;
	char **commande;
	int pid;

	*av = NULL;
	if (ac == 0)
		return 1;
	path_splitted = get_path(env);
	char *ok;
	while (1)
	{
		commande = get_input();
		ok = ft_strjoin(path_splitted[4], "/");
		
		ok = ft_strjoin(ok, commande[0]);
		pid = fork();
		if (pid == 0)
		{
			if (execve(ok, commande, env) == -1)
				perror("error ");
		}
			
		else
			(waitpid(pid, NULL, 0));
	}
	
	
	
}
