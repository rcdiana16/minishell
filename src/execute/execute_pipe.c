/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:59:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/02 17:34:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_builtin_or_exit_pipe(char **path_sp_w_slash, char **cmd_inf, \
	t_env *env_list, t_command *stru)
{
	char		*built_in_path;

	built_in_path = find_no_builtin(path_sp_w_slash, cmd_inf);
	if (!built_in_path)
	{
		//free_arr(stru->envp);
		exec_builtin_or_exit_pipe(cmd_inf, \
		stru, env_list, path_sp_w_slash);
	}
	return (built_in_path);
}

int	execute_child_process_pipe(char **cmd_info, char **path_sp_w_slash, \
	t_env *env_list, t_command *stru)
{
	char	*built_in_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_info[0])
		return (0);
	stru->envp = convert_env_to_array(env_list);
	if (cmd_info[0][0] == '/' || \
	ft_strchr(cmd_info[0], '/') != NULL)
	{
		execve(cmd_info[0], cmd_info, stru->envp);
		//free_arr(stru->envp);
		exec_builtin_or_exit_pipe(cmd_info, \
		stru, env_list, path_sp_w_slash);
	}
	built_in_path = find_builtin_or_exit_pipe(path_sp_w_slash, \
		cmd_info, env_list, stru);
	execve(built_in_path, cmd_info, stru->envp);
	//free_arr(stru->envp);
	free(built_in_path);
	exec_builtin_or_exit_pipe(cmd_info, stru, env_list, \
	path_sp_w_slash);
	return (0);
}
/*
void	handle_redirection(char **cmd_tokens, t_command *cmd_info, int *i)
{
	if (ft_strncmp(cmd_tokens[*i], ">>", 2) == 0)
	{
		if (cmd_tokens[*i + 1])
		{
			cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
			cmd_info->c_append = 1;
			cmd_info->c_red_o = 0;
			cmd_info->c_red_i = 0;
			*i += 2;
			return ;
		}
	}
	else if (ft_strncmp(cmd_tokens[*i], ">", 1) == 0)
	{
		if (cmd_tokens[*i + 1] && cmd_tokens[*i + 1][0] != '\0')
		{
			cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
			cmd_info->c_red_o = 1;
			cmd_info->c_append = 0;
			cmd_info->c_red_i = 0;
			*i += 2;
			return ;
		}
	}
	if (ft_strncmp(cmd_tokens[*i], "<<", 2) == 0)
	{
		if (cmd_tokens[*i + 1])
		{
			here_doc(cmd_tokens[*i + 1], &cmd_info->fd_here_doc);
			dup2(cmd_info->fd_here_doc, 0);
			close(cmd_info->fd_here_doc);
			cmd_info->here_doc = 1;
			cmd_info->c_append = 0;
			cmd_info->c_red_o = 0;
			cmd_info->c_red_i = 0;
			*i += 2;
			return ;
		}
	}
	else if (ft_strncmp(cmd_tokens[*i], "<", 1) == 0)
	{
		if (cmd_tokens[*i + 1] && cmd_tokens[*i + 1][0] != '\0')
		{
			cmd_info->file_in = ft_strdup(cmd_tokens[*i + 1]);
			cmd_info->c_red_i = 1;
			cmd_info->c_append = 0;
			cmd_info->c_red_o = 0;
			*i += 2;
			return ;
		}
	}
}*/

char	**allocate_cleaned_cmd(char **cmd_tokens)
{
	int		i;
	char	**cleaned_cmd;

	i = 0;
	while (cmd_tokens[i])
		i++;
	if (i == 0)
		return (NULL);
	cleaned_cmd = malloc(sizeof(char *) * (i + 1));
	cleaned_cmd[i] = NULL;
	return (cleaned_cmd);
}

void	filter_and_copy_tokens(char **cmd_tokens, t_command *cmd_info, \
		char **cleaned_cmd, t_pipe_exec_info *pipe_exec_info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!cmd_tokens)
		return ;
	while (cmd_tokens[i])
	{
		if ((ft_strncmp(cmd_tokens[i], ">", 1) == 0 || \
		ft_strncmp(cmd_tokens[i], ">>", 2) == 0 || \
		ft_strncmp(cmd_tokens[i], "<", 1) == 0 || \
		ft_strncmp(cmd_tokens[i], "<<", 2) == 0) && (cmd_tokens[i + 1]))
			handle_redirection(cmd_tokens, cmd_info, &i, pipe_exec_info);
		else
		{
			if (cmd_tokens[i])
				cleaned_cmd[j++] = ft_strdup(cmd_tokens[i]);
			i++;
		}
	}
	cleaned_cmd[j] = NULL;
}

char	**clean_redir(char **cmd_tokens, t_command *cmd_info, t_pipe_exec_info *pipe_exec_info)
{
	char	**cleaned_cmd;

	cleaned_cmd = allocate_cleaned_cmd(cmd_tokens);
	if (!cleaned_cmd)
		return (NULL);
	filter_and_copy_tokens(cmd_tokens, cmd_info, cleaned_cmd, pipe_exec_info);
	/*if (cmd_tokens)
		free_arr(cmd_tokens);*/
	if (cmd_tokens != cleaned_cmd)
		free_arr(cmd_tokens);
	return (cleaned_cmd);
}
/*
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
		if ((ft_strncmp(cmd_tokens[i], ">", 1) == 0 || \
		ft_strncmp(cmd_tokens[i], ">>", 2) == 0 || \
		ft_strncmp(cmd_tokens[i], "<", 1) == 0 || \
		ft_strncmp(cmd_tokens[i], "<<", 2) == 0) && (cmd_tokens[i + 1]))
			handle_redirection(cmd_tokens, cmd_info, &i);
		else
		{
			cleaned_cmd[j++] = ft_strdup(cmd_tokens[i]);
			i++;
		}
	}
	cleaned_cmd[j] = NULL;
	free_arr(cmd_tokens);
	return (cleaned_cmd);
}*/
