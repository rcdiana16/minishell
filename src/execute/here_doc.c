/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:33:31 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/02 17:38:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

/*
void	here_doc(char *delimiter)
{
	char				*line;
	int					pipefd[2];
	ssize_t				len;
	struct sigaction	sa_new;
	struct sigaction	sa_old;

	g_heredoc_interrupted = 0;
	line = NULL;
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	sa_new.sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	while (1)
	{
		if (g_heredoc_interrupted)
		{
			free(line);
			close(pipefd[0]);
			close(pipefd[1]);
			sigaction(SIGINT, &sa_old, NULL);
			return ;
		}
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			break ;
		}
		if (g_heredoc_interrupted)
		{
			free(line);
			close(pipefd[0]);
			close(pipefd[1]);
			sigaction(SIGINT, &sa_old, NULL);
			return ;
		}
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strncmp(line, delimiter, len) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	sigaction(SIGINT, &sa_old, NULL);
}*/
void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
}

static void	init_here_doc_signals(struct sigaction *sa_new, \
	struct sigaction *sa_old)
{
	sa_new->sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa_new->sa_mask);
	sa_new->sa_flags = 0;
	sigaction(SIGINT, sa_new, sa_old);
}

static int	check_heredoc_interrupt(char *line, int *pipefd, \
	struct sigaction *sa_old)
{
	if (g_heredoc_interrupted)
	{
		free(line);
		close(pipefd[0]);
		close(pipefd[1]);
		sigaction(SIGINT, sa_old, NULL);
		return (1);
	}
	return (0);
}

static int	process_heredoc_line(char *line, char *delimiter, int *pipefd)
{
	ssize_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strncmp(line, delimiter, len) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
	return (0);
}

void	here_doc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
	char				*line;
	int					pipefd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;

	g_heredoc_interrupted = 0;
	line = NULL;
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	init_here_doc_signals(&sa_new, &sa_old);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		line = replace_env_vars(line, pipe_exec_info->env_list, \
			pipe_exec_info->shell);
		if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
			break ;
		if (check_heredoc_interrupt(line, pipefd, &sa_old))
			break ;
		if (process_heredoc_line(line, delimiter, pipefd))
			break ;
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	sigaction(SIGINT, &sa_old, NULL);
}
