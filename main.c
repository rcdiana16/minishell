/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/01 18:50:50 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		**path_splitted;
	char		**path_sp_w_slash;
	t_command	*cmd_info;
	t_env		*env_list;
	int			pid;
	char		*built_in_path;

	*av = NULL;
	path_sp_w_slash = NULL;
	path_splitted = NULL;
	built_in_path = NULL;
	cmd_info = 0;
	env_list = 0;
	if (ac == 0)
		return (1);
	path_splitted = get_path();
	if (!path_splitted)
	{
		fprintf(stderr, "Error: get_path() returned NULL\n");
		exit(1);
	}
	get_list_env(env, env_list);
	while (1)
	{
		cmd_info = get_input();
		if (!cmd_info || !cmd_info->tokens || !cmd_info->tokens[0])
		{
			free_command(cmd_info);
			continue ;
		}
		if ((ft_strncmp(cmd_info->tokens[0], "exit", ft_strlen(cmd_info->tokens[0]))) == 0)
		{
			exit(1);
			return (1);
		}
		path_sp_w_slash = add_slash(path_splitted);
		if (!path_sp_w_slash)
		{
			fprintf(stderr, "Error: add_slash() returned NULL\n");
			exit(1);
		}
		built_in_path = find_no_builtin(path_sp_w_slash, cmd_info->tokens);
		if (!built_in_path)
		{
			fprintf(stderr, "Error: find_no_builtin() returned NULL\n");
			exit(1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (check_builtins(cmd_info->tokens) != 1)
			{
				if (execve(built_in_path, cmd_info->tokens, env) == -1)
					perror("error ");
			}
			free_arr(path_sp_w_slash);
			free_command(cmd_info);
			free(built_in_path);
			free_node(env_list);
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
