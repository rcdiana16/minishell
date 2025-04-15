/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:04:23 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 16:15:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
char	**check_redir(t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd_info->tokens[i])
		i++;
	if ((cmd_info->c_red_o == 1 || cmd_info->c_append == 1) && i >= 2)
	{
		cmd_info->file_out = ft_strdup(cmd_info->tokens[i - 1]);
		free(cmd_info->tokens[i - 2]);
		cmd_info->tokens[i - 2] = NULL;
		free(cmd_info->tokens[i - 1]);
		cmd_info->tokens[i - 1] = NULL;
		cmd_info->tokens[i - 2] = cmd_info->tokens[i];
		cmd_info->tokens[i - 1] = NULL;
	}
	return (cmd_info->tokens);
}
*/
int	open_file(char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 3)
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, file, ft_strlen(file));
		//write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	return (fd);
}

int	manage_redirection(t_command *cmd_info)
{
	if (cmd_info->c_red_i == 1)
	{
		if (!cmd_info->file_in || cmd_info->file_in[0] == '\0')
			return (2);
		cmd_info->fd_in = open_file(cmd_info->file_in, 3);
		if (cmd_info->fd_in == -1)
			return (0);
		dup2(cmd_info->fd_in, STDIN_FILENO);
		close(cmd_info->fd_in);
	}
	else if ((cmd_info->c_red_o == 1 || cmd_info->c_append == 1))
	{
		if (!cmd_info->file_out || cmd_info->file_out[0] == '\0')
			return (-1);
		if (cmd_info->c_red_o == 1)
			cmd_info->fd_out = open_file(cmd_info->file_out, 1);
		else if (cmd_info->c_append == 1)
			cmd_info->fd_out = open_file(cmd_info->file_out, 2);
		if (cmd_info->fd_out == -1)
			return (0);
		dup2(cmd_info->fd_out, STDOUT_FILENO);
		close(cmd_info->fd_out);
	}
	return (1);
}

void	execute_in_child(t_command *cmd_info, \
	char **path_sp_w_slash, t_env *env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_child_process(cmd_info, path_sp_w_slash, env_list);
}
