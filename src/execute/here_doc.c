/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:33:31 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/31 17:37:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_next_line_pip(char **output_line)
{
	char	*temp_buffer;
	int		char_count;
	int		bytes_read;
	char	current_char;

	char_count = 0;
	bytes_read = 0;
	temp_buffer = (char *)malloc(10000);
	if (!temp_buffer)
		return (-1);
	bytes_read = read(0, &current_char, 1);
	while (bytes_read && current_char != '\n' && current_char != '\0')
	{
		if (current_char != '\n' && current_char != '\0')
			temp_buffer[char_count] = current_char;
		char_count++;
		bytes_read = read(0, &current_char, 1);
	}
	temp_buffer[char_count] = '\n';
	temp_buffer[++char_count] = '\0';
	*output_line = temp_buffer;
	return (bytes_read);
}

void	here_doc(char *limiter, int *fd)
{
	char	*line;

	create_pipe(fd);
	while (get_next_line_pip(&line))
	{
		if (ft_strlen(line) - 1 == ft_strlen(limiter) && \
		ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
}

void	handle_heredoc_redirection(char **cmd_tokens, t_command *cmd_info, \
	int *i)
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
	}
}
