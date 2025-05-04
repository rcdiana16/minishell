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
/*
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
		int tty_fd = open("/dev/tty", O_RDONLY);
		line = get_next_line(tty_fd);
		close(tty_fd);
		if (line)
			line = replace_env_vars(line, pipe_exec_info->env_list, \
			pipe_exec_info->shell);
		if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
			break ;
				if (process_heredoc_line(line, delimiter, pipefd))
			break ;
	}
	while (1)
{
	write(STDOUT_FILENO, "> ", 2);
	int tty_fd = open("/dev/tty", O_RDONLY);
	char *tmp = get_next_line(tty_fd);
	close(tty_fd);

	if (tmp)
	{
		char *expanded = replace_env_vars(tmp, pipe_exec_info->env_list, pipe_exec_info->shell);
		free(tmp);
		line = expanded;
	}
	else
		line = NULL;

	if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
	{
		free(line);
		break;
	}
	if (process_heredoc_line(line, delimiter, pipefd))
		break;
}

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	sigaction(SIGINT, &sa_old, NULL);
//	get_next_line(-42);
}*/
/*
void	here_doc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
	char				*line;
	int					pipefd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;
	int					input_fd;
	int					line_limit = 1000;

	g_heredoc_interrupted = 0;
	line = NULL;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);

	init_here_doc_signals(&sa_new, &sa_old);

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);

		if (isatty(STDIN_FILENO))
			input_fd = open("/dev/tty", O_RDONLY);
		else
			input_fd = STDIN_FILENO;

		if (input_fd < 0)
		{
			perror("minishell: heredoc input error");
			break;
		}

		char *tmp = get_next_line(input_fd);
		if (isatty(STDIN_FILENO))
			close(input_fd);  // Don't close STDIN_FILENO

		if (tmp)
		{
			char *expanded = replace_env_vars(tmp, pipe_exec_info->env_list, pipe_exec_info->shell);
			free(tmp);
			line = expanded;
		}
		else
			line = NULL;

		if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
		{
			free(line);
			break;
		}

		if (process_heredoc_line(line, delimiter, pipefd))
			break;

		if (!isatty(STDIN_FILENO) && --line_limit <= 0)
		{
			write(STDERR_FILENO, "minishell: heredoc line limit reached\n", 38);
			break;
		}
	}

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);

	sigaction(SIGINT, &sa_old, NULL);
	get_next_line(-42);  // Clean up static buffer
}
*/
/*best
void	here_doc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
	char				*line;
	int					pipefd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;
	int					input_fd;
	int					line_limit = 1000;

	g_heredoc_interrupted = 0;
	line = NULL;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);

	init_here_doc_signals(&sa_new, &sa_old);

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);

		// Use /dev/tty only in truly interactive mode (no pipes/scripts)
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			input_fd = open("/dev/tty", O_RDONLY);
		else
			input_fd = STDIN_FILENO;

		if (input_fd < 0)
		{
			perror("minishell: heredoc input error");
			break;
		}

		char *tmp = get_next_line(input_fd);
		if (input_fd != STDIN_FILENO)
			close(input_fd);

		if (tmp)
		{
			char *expanded = replace_env_vars(tmp, pipe_exec_info->env_list, pipe_exec_info->shell);
			free(tmp);
			line = expanded;
		}
		else
			line = NULL;

		if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
		{
			free(line);
			break;
		}

		if (process_heredoc_line(line, delimiter, pipefd))
			break;

		if (!isatty(STDIN_FILENO) && --line_limit <= 0)
		{
			write(STDERR_FILENO, "minishell: heredoc line limit reached\n", 38);
			break;
		}
	}

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	sigaction(SIGINT, &sa_old, NULL);

	// Free internal static buffer in get_next_line, if your implementation supports this
	get_next_line(-42);
}
*/
/*good for no < < < <
void here_doc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
    char                *line;
    int                 pipefd[2];
    struct sigaction    sa_new;
    struct sigaction    sa_old;

    g_heredoc_interrupted = 0;
    line = NULL;
    
    // Create the pipe for heredoc
    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    // Initialize the signal handlers
    init_here_doc_signals(&sa_new, &sa_old);

    // Loop to read lines for the heredoc input
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);  // Print the prompt
        int tty_fd = open("/dev/tty", O_RDONLY);  // Open /dev/tty for reading input
        char *tmp = get_next_line(tty_fd);  // Get the next line from the terminal
        close(tty_fd);

        if (tmp)
        {
            // Replace environment variables in the input line
            char *expanded = replace_env_vars(tmp, pipe_exec_info->env_list, pipe_exec_info->shell);
            free(tmp);
            line = expanded;
        }
        else
        {
            line = NULL;  // No more input
        }

        // Check if we reached the delimiter or an interrupt signal
        if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
        {
            free(line);
            break;
        }

        // Process the heredoc line (write it to the pipe)
        if (process_heredoc_line(line, delimiter, pipefd))
            break;
    }

    // Check if the heredoc should be attached to STDIN based on the pipe flag
    if (pipe_exec_info->cmd_info->c_pipe != 0)
    {
        // If there's a pipe (pipe != 0), attach the heredoc content to STDIN
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);  // Attach to stdin
        close(pipefd[0]);
    }
    else
    {
        // If there's no pipe, just close the pipe ends (discard the content)
        close(pipefd[0]);
        close(pipefd[1]);
    }

    // Restore the previous signal action for SIGINT
    sigaction(SIGINT, &sa_old, NULL);
	get_next_line(-42);
}*/

void	here_doc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
	char				*line;
	int					pipefd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;
	int					input_fd;
	int					line_limit = 1000;

	g_heredoc_interrupted = 0;
	line = NULL;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);

	init_here_doc_signals(&sa_new, &sa_old);

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);

		// Use tty if interactive, stdin otherwise
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			input_fd = open("/dev/tty", O_RDONLY);
		else
			input_fd = STDIN_FILENO;

		if (input_fd < 0)
		{
			perror("minishell: heredoc input error");
			break;
		}
		char *tmp = get_next_line(input_fd);	
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (tmp)
		{
			char *expanded = replace_env_vars(tmp, pipe_exec_info->env_list, pipe_exec_info->shell);
			free(tmp);
			line = expanded;
		}
		else
			line = NULL;

		if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
		{
			free(line);
			break;
		}

		if (process_heredoc_line(line, delimiter, pipefd))
			break;

		if (!isatty(STDIN_FILENO) && --line_limit <= 0)
		{
			write(STDERR_FILENO, "minishell: heredoc line limit reached\n", 38);
			break;
		}
	}

	close(pipefd[1]);

	// ✅ Always redirect pipe output to STDIN
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);

	sigaction(SIGINT, &sa_old, NULL);

	get_next_line(-42); // cleanup static buffer if supported
}

