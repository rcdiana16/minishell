/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:59:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/24 11:31:52 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_builtin_or_exit_pipe(char **path_sp_w_slash, char **cmd_inf, \
	t_env *env_list)
{
	char		*built_in_path;
	t_command	*cm_pl;

	cm_pl = NULL;
	built_in_path = find_no_builtin(path_sp_w_slash, cmd_inf);
	if (!built_in_path)
		exec_builtin_or_exit_pipe(cmd_inf[0], \
		cm_pl, env_list, path_sp_w_slash);
	return (built_in_path);
}

void	exec_builtin_or_exit_pipe(char *command, t_command *cmd_info, \
	t_env *env_list, char **path_sp_w_slash)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	free_all(cmd_info, path_sp_w_slash, env_list);
	exit(127);
}

int	execute_child_process_pipe(char **cmd_info, char **path_sp_w_slash, \
	t_env *env_list, t_command *stru)
{
	char	*built_in_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_info[0])
		return (0);
	if ((stru->c_append || stru->c_red_o) && stru->file_out)
	{
		if (!manage_redirection(stru))
			exit(1);
	}
	if (cmd_info[0][0] == '/' || \
	ft_strchr(cmd_info[0], '/') != NULL)
	{
		execve(cmd_info[0], cmd_info, \
		convert_env_to_array(env_list));
		exec_builtin_or_exit_pipe(cmd_info[0], \
		stru, env_list, path_sp_w_slash);
	}
	built_in_path = find_builtin_or_exit_pipe(path_sp_w_slash, \
		cmd_info, env_list);
	execve(built_in_path, cmd_info, convert_env_to_array(env_list));
	exec_builtin_or_exit_pipe(cmd_info[0], stru, env_list, \
	path_sp_w_slash);
	return (0);
}

void	handle_redirection(char **cmd_tokens, t_command *cmd_info, int *i)
{
	if (ft_strncmp(cmd_tokens[*i], ">", 1) == 0 || \
	ft_strncmp(cmd_tokens[*i], ">>", 2) == 0)
	{
		if (cmd_tokens[*i + 1])
		{
			cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
			cmd_info->c_red_o = (ft_strncmp(cmd_tokens[*i], ">", 1) == 0);
			cmd_info->c_append = (ft_strncmp(cmd_tokens[*i], ">>", 2) == 0);
			*i += 2;
		}
	}
}

char	**clean_redir(char **cmd_tokens, t_command *cmd_info)
{
	int		i;
	int		j;
	char	**cleaned_cmd;

	i = 0;
	j = 0;
	while (cmd_tokens[i])
		i++;
	cleaned_cmd = malloc(sizeof(char *) * (i + 1));
	if (!cleaned_cmd)
		return (NULL);
	i = 0;
	while (cmd_tokens[i])
	{
		if (ft_strncmp(cmd_tokens[i], ">", 1) == 0 || \
		ft_strncmp(cmd_tokens[i], ">>", 2) == 0)
			handle_redirection(cmd_tokens, cmd_info, &i);
		else
		{
			cleaned_cmd[j++] = ft_strdup(cmd_tokens[i]);
			i++;
		}
	}
	cleaned_cmd[j] = NULL;
	return (cleaned_cmd);
}
