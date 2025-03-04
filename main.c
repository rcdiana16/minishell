/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/04 21:21:41 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handle_path(char ***path_splitted, char ***path_sp_w_slash, \
	t_env *env_mini)
{
	*path_splitted = get_path(env_mini);
	if (!*path_splitted)
	{
		write(2, "Error: get_path() returned NULL\n", \
			ft_strlen("Error: get_path() returned NULL\n"));
		exit(1);
	}
	*path_sp_w_slash = add_slash(*path_splitted);
	if (!*path_sp_w_slash)
	{
		write(2, "Error: add_slash() returned NULL\n", \
			ft_strlen("Error: add_slash() returned NULL\n"));
		exit(1);
	}
}

int	execute_child_process(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	char	*built_in_path;

	if (cmd_info->tokens[0][0] == '/' || \
		ft_strchr(cmd_info->tokens[0], '/') != NULL)
	{
		execve(cmd_info->tokens[0], cmd_info->tokens, \
			convert_env_to_array(env_list));
		perror("execve");
		exit(1);
	}
	built_in_path = find_no_builtin(path_sp_w_slash, cmd_info->tokens);
	if (!built_in_path)
	{
		write(2, "Command not found: ", ft_strlen("Command not found: "));
		write(2, cmd_info->tokens[0], ft_strlen(cmd_info->tokens[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(built_in_path, cmd_info->tokens, convert_env_to_array(env_list));
	perror("execve");
	exit(1);
	return (0);
}

int	execute_command(t_command *cmd_info, char **path_sp_w_slash, \
	t_env *env_list)
{
	int	pid;

	if (check_builtins(cmd_info->tokens, env_list))
	{
		free_command(cmd_info);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd_info, path_sp_w_slash, env_list);
	else
	{
		waitpid(pid, NULL, 0);
		free_command(cmd_info);
	}
	return (0);
}

int	handle_input(t_command **cmd_info, t_env *env_mini)
{
	*cmd_info = get_input(env_mini);
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
	env_list = initialize_environment(env, env_list);
	while (1)
	{
		handle_path(&path_splitted, &path_sp_w_slash, env_list);
		if (handle_input(&cmd_info, env_list))
			continue ;
		if (execute_command(cmd_info, path_sp_w_slash, env_list))
			continue ;
	}
	return (0);
}
