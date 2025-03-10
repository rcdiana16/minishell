/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:16 by diana             #+#    #+#             */
/*   Updated: 2025/03/10 21:02:07 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	g_code = 0;

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
	/*int i = 0;
	while (path_splitted[i])
	{
		free(path_splitted[i]);
		i++;
	}
	//free(path_splitted);*/
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

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

int	handle_input(t_command **cmd_info, t_env *env_mini, int mode)
{
	*cmd_info = get_input(env_mini, mode);
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
	disable_echoctl();
	set_signals();
	while (1)
	{
		handle_path(&path_splitted, &path_sp_w_slash, env_list);
		/*int i = 0;
		while (path_splitted[i])
		{
			free(path_splitted[i]);
			i++;
		}
		free(path_splitted);*/
		if (isatty(STDIN_FILENO))
		{
			if (handle_input(&cmd_info, env_list, 0))
				continue ;
		}
		else{
			if (handle_input(&cmd_info, env_list,1))
				continue ;
		}
		if (execute_command(cmd_info, path_sp_w_slash, env_list))
			continue ;
		/*int i = 0;
		while (path_sp_w_slash[i])
		{
			free(path_sp_w_slash[i]);
			i++;
		}*/
	}
	return (0);
}

int	get_gcode(void)
{
	return (g_code);
}

void	set_gcode(int val)
{
	g_code = val;
}
