/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/02 22:44:15 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handle_path(char ***path_splitted, char ***path_sp_w_slash)
{
	*path_splitted = get_path();
	if (!*path_splitted)
	{
		fprintf(stderr, "Error: get_path() returned NULL\n");
		exit(1);
	}
	*path_sp_w_slash = add_slash(*path_splitted);
	if (!*path_sp_w_slash)
	{
		fprintf(stderr, "Error: add_slash() returned NULL\n");
		exit(1);
	}
}

t_env	*initialize_environment(char **env, t_env *env_list)
{
	return (get_list_env(env, env_list));
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	char **env, t_env *env_list)
{
	char	*built_in_path;
	int		pid;

	built_in_path = NULL;
	if (check_builtins(cmd_info->tokens, env_list))
	{
		free_command(cmd_info);
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		built_in_path = find_no_builtin(path_sp_w_slash, cmd_info->tokens);
		if (execve(built_in_path, cmd_info->tokens, env) == -1)
		{
			perror("error ");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free_command(cmd_info);
	}
	return (0);
}

int	handle_input(t_command **cmd_info)
{
	*cmd_info = get_input();
	if (!*cmd_info || !(*cmd_info)->tokens || !(*cmd_info)->tokens[0])
	{
		free_command(*cmd_info);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		**path_splitted;
	char		**path_sp_w_slash;
	t_command	*cmd_info;
	t_env		*env_list;

	*av = NULL;
	path_splitted = NULL;
	path_sp_w_slash = NULL;
	cmd_info = NULL;
	env_list = NULL;
	if (ac == 0)
		return (1);
	handle_path(&path_splitted, &path_sp_w_slash);
	env_list = initialize_environment(env, env_list);
	while (1)
	{
		if (handle_input(&cmd_info))
			continue ;
		if (execute_command(cmd_info, path_sp_w_slash, env, env_list))
			continue ;
	}
	return (0);
}
