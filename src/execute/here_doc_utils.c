/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:21:20 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/06 18:14:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t   g_heredoc_interrupted = 0;

void    sigint_handler_heredoc(int sig)
{
        (void)sig;
        g_heredoc_interrupted = 1;
        write(STDOUT_FILENO, "\n", 1);
}

static void     init_here_doc_signals(struct sigaction *sa_new, \
        struct sigaction *sa_old)
{
        sa_new->sa_handler = sigint_handler_heredoc;
        sigemptyset(&sa_new->sa_mask);
        sa_new->sa_flags = 0;
        sigaction(SIGINT, sa_new, sa_old);
}

static int      check_heredoc_interrupt(char *line, int *pipefd, \
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

static int      process_heredoc_line(char *line, char *delimiter, int *pipefd)
{
        ssize_t len;

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
static int      handle_heredoc_input(char *delimiter)
{
        char                            *line;
        int                                     pipefd[2];
        int                                     input_fd;
        struct sigaction        sa_new;
        struct sigaction        sa_old;

        g_heredoc_interrupted = 0;
        if (pipe(pipefd) == -1)
                return (-1);
        init_here_doc_signals(&sa_new, &sa_old);
        while (1)
        {
                write(STDOUT_FILENO, "> ", 2);
                if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
                        input_fd = open("/dev/tty", O_RDONLY);
                else
                        input_fd = STDIN_FILENO;
                if (input_fd < 0)
                {
                        perror("minishell: heredoc input error");
                        close(pipefd[0]);
                        close(pipefd[1]);
                        return (-1);
                }
                line = get_next_line(input_fd);
                if (input_fd != STDIN_FILENO)
                        close(input_fd);
                if (!line || check_heredoc_interrupt(line, pipefd, &sa_old))
                        break ;
                if (process_heredoc_line(line, delimiter, pipefd))
                        break ;
        }
        close(pipefd[1]);
        sigaction(SIGINT, &sa_old, NULL);
        return (pipefd[0]);
}*/

static int      init_heredoc_io(void)
{
        if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
                return (open("/dev/tty", O_RDONLY));
        return (STDIN_FILENO);
}

static int      handle_heredoc_loop(char *delimiter, \
int pipefd[2], struct sigaction *sa_old)
{
        char    *line;
        int             input_fd;

        while (1)
        {
                write(STDOUT_FILENO, "> ", 2);
                input_fd = init_heredoc_io();
                if (input_fd < 0)
                {
                        perror("minishell: heredoc input error");
                        close(pipefd[0]);
                        close(pipefd[1]);
                        return (-1);
                }
                line = get_next_line(input_fd);
                if (input_fd != STDIN_FILENO)
                        close(input_fd);
                if (!line || check_heredoc_interrupt(line, pipefd, sa_old))
                        break ;
                if (process_heredoc_line(line, delimiter, pipefd))
                        break ;
        }
        return (0);
}

static int      handle_heredoc_input(char *delimiter)
{
        int                                     pipefd[2];
        struct sigaction        sa_new;
        struct sigaction        sa_old;

        g_heredoc_interrupted = 0;
        if (pipe(pipefd) == -1)
                return (-1);
        init_here_doc_signals(&sa_new, &sa_old);
        if (handle_heredoc_loop(delimiter, pipefd, &sa_old) == -1)
                return (-1);
        close(pipefd[1]);
        sigaction(SIGINT, &sa_old, NULL);
        return (pipefd[0]);
}

int     execute_heredoc(char *delimiter, t_pipe_exec_info *pipe_exec_info)
{
        int     heredoc_fd;
        int     saved_stdin;

        heredoc_fd = handle_heredoc_input(delimiter);
        if (heredoc_fd == -1)
                return (-1);
        saved_stdin = dup(STDIN_FILENO);
        if (saved_stdin == -1)
        {
                close(heredoc_fd);
                return (-1);
        }
        if (dup2(heredoc_fd, STDIN_FILENO) == -1)
        {
                close(heredoc_fd);
                close(saved_stdin);
                return (-1);
        }
        pipe_exec_info->cmd_info->fd_here_doc = saved_stdin;
        pipe_exec_info->cmd_info->here_doc = 1;
        pipe_exec_info->cmd_info->fd_in = heredoc_fd;
        return (0);
}

void    restore_heredoc_stdin(t_command *cmd_info)
{
        if (cmd_info->here_doc)
        {
                if (dup2(cmd_info->fd_here_doc, STDIN_FILENO) == -1)
                {
                        perror("minishell: dup2");
                }
                close(cmd_info->fd_here_doc);
                cmd_info->fd_here_doc = -1;
                close(cmd_info->fd_in);
                cmd_info->fd_in = -1;
                cmd_info->here_doc = 0;
        }
}

void    handle_heredoc_redirection(char **cmd_tokens, \
        t_command *cmd_info __attribute__((unused)), int *i, t_pipe_exec_info *pipe_exec_info)
{
        if (cmd_tokens[*i + 1])
        {
                if (execute_heredoc(cmd_tokens[*i + 1], pipe_exec_info) == -1)
                {
                        *i += 2;
                        return ;
                }
                *i += 2;
        }
}
