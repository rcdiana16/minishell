/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/02/25 20:18:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**path_splitted;
	char **commande;

	*av = NULL;
	if (ac == 0)
		return 1;
	path_splitted = get_path(env);
	commande = get_input();
	execve(path_splitted[5], commande, env);
}
