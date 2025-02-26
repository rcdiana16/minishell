/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/02/26 21:46:57 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		**path_splitted;
	char		**test;
	t_command	*cmd_info;
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
		//call function add slash to path splitted
		//call function to find the good path(path_splitted) == good_path
		//find_ex_path(path_splitted)
		test = add_slash(path_splitted);
		temp = add_command(test, cmd_info->tokens);
		//ok = ft_strjoin(ok, cmd_info->tokens[0]);
		//free(temp);
		
		pid = fork();
		if (pid == 0)
		{
			if (execve(temp, cmd_info->tokens, env) == -1)
				perror("error ");
			i = 0;
			while (path_splitted[i])
			{
				free(path_splitted[i]);
				i++;
			}
			free(path_splitted);
			free_command(cmd_info);
			exit(1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			free_command(cmd_info);
		}
	}
	
	return (0);
}
