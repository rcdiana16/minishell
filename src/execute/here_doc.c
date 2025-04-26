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

volatile sig_atomic_t g_heredoc_interrupted = 0;

void sigint_handler_heredoc(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(STDOUT_FILENO, "\n", 1);
}

void here_doc(char *delimiter) {
    char *line = NULL;
    int pipefd[2];
    ssize_t len;
    struct sigaction sa_new;
    struct sigaction sa_old;
	g_heredoc_interrupted = 0;
    // Créer un pipe
    if (pipe(pipefd) == -1) {
        //perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Modifier le comportement du signal SIGINT pour heredoc
    sa_new.sa_handler = sigint_handler_heredoc;
    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = 0;
    sigaction(SIGINT, &sa_new, &sa_old);
    while (1) {
        if (g_heredoc_interrupted) {
            free(line);
            close(pipefd[0]);
            close(pipefd[1]);
            sigaction(SIGINT, &sa_old, NULL); // Restaure le signal original
            return; // On quitte proprement
        }

        write(STDOUT_FILENO, "> ", 2);
        
        line = get_next_line(STDIN_FILENO);
        if (!line) {
            break;
        }
		if (g_heredoc_interrupted) {
			free(line);
			close(pipefd[0]);
			close(pipefd[1]);
			sigaction(SIGINT, &sa_old, NULL);
			return;
		}
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        if (ft_strncmp(line, delimiter, len) == 0) {
            free(line);
            break;
        }

        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);

        free(line);
    }

    // Fermer écriture
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    // Restaurer le comportement original de SIGINT
    sigaction(SIGINT, &sa_old, NULL);
}


void	handle_heredoc_redirection(char **cmd_tokens, t_command *cmd_info, int *i)
{
	int saved_stdin;

	if (cmd_tokens[*i + 1])
	{
		here_doc(cmd_tokens[*i + 1]);
		saved_stdin = dup(0); // <--- SAVE stdin
		//dup2(cmd_info->fd_here_doc, 0); // replace stdin by heredoc pipe
		//close(cmd_info->fd_here_doc);
		cmd_info->fd_here_doc = saved_stdin; // store it for later restoration
		cmd_info->here_doc = 1;
		cmd_info->c_append = 0;
		cmd_info->c_red_o = 0;
		cmd_info->c_red_i = 0;
		*i += 2;
	}
}

