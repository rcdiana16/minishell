/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/02/28 21:16:20 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		**path_splitted;
	char		**path_sp_w_slash;
	t_command	*cmd_info;
	int			pid;
	int			i;
	char		*built_in_path;

	*av = NULL;
	if (ac == 0)
		return (1);
	path_splitted = get_path();
	get_list_env(env);
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
		path_sp_w_slash = add_slash(path_splitted);
		built_in_path = find_no_builtin(path_sp_w_slash, cmd_info->tokens);
		if ((ft_strncmp(cmd_info->tokens[0], "exit", ft_strlen(cmd_info->tokens[0]))) == 0)
		{
			exit(1);
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (check_builtins(cmd_info->tokens) != 1)
			{
				if (execve(built_in_path, cmd_info->tokens, env) == -1)
					perror("error ");
			}
			i = 0;
			while (path_splitted[i])
			{
				free(path_splitted[i]);
				i++;
			}
			free(path_splitted);
			
			//free(built_in_path);
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
