/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:32:15 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/05 10:16:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     handle_append_redirection(char **cmd_tokens, t_command *cmd_info, \
                int *i)
{
        if (cmd_tokens[*i + 1])
        {
                if (cmd_info->file_out)
                        free(cmd_info->file_out);
                cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
                cmd_info->fd_out = open_file(cmd_info->file_out, 2, cmd_info);
                cmd_info->c_append = 1;
                cmd_info->c_red_o = 0;
                /* Don't reset input redirection flag */
                *i += 2;
        }
        if (cmd_info->fd_out == -1)
                return (-1);
        return (1);
}

int     handle_output_redirection(char **cmd_tokens, t_command *cmd_info, \
                int *i)
{
        if (cmd_tokens[*i + 1] && cmd_tokens[*i + 1][0] != '\0')
        {
                if (cmd_info->file_out)
                        free(cmd_info->file_out);
                cmd_info->file_out = ft_strdup(cmd_tokens[*i + 1]);
                cmd_info->fd_out = open_file(cmd_info->file_out, 1, cmd_info);
                cmd_info->c_red_o = 1;
                cmd_info->c_append = 0;
                /* Don't reset input redirection flag */
                *i += 2;
        }
        if (cmd_info->fd_out == -1)
                return (-1);
        return (1);
}

int     handle_input_redirection(char **cmd_tokens, t_command *cmd_info, int *i)
{
        if (cmd_tokens[*i + 1] && cmd_tokens[*i + 1][0] != '\0')
        {
                if (cmd_info->file_in)
                        free(cmd_info->file_in);
                cmd_info->file_in = ft_strdup(cmd_tokens[*i + 1]);
                cmd_info->fd_in = open_file(cmd_info->file_in, 3, cmd_info);
                cmd_info->c_red_i = 1;
                /* Don't reset output redirection flags */
                *i += 2;
        }
        if (cmd_info->fd_in == -1)
                return (-1);
        return (1);
}

int     handle_redirection(char **cmd_tokens, t_command *cmd_info, int *i, \
                t_pipe_exec_info *pipe_exec_info)
{
        int ret;

        ret = 0;
        if (ft_strncmp(cmd_tokens[*i], ">>", 2) == 0)
                ret = handle_append_redirection(cmd_tokens, cmd_info, i);
        else if (ft_strncmp(cmd_tokens[*i], ">", 1) == 0)
                ret = handle_output_redirection(cmd_tokens, cmd_info, i);
        else if (ft_strncmp(cmd_tokens[*i], "<<", 2) == 0)
                handle_heredoc_redirection(cmd_tokens, cmd_info, i, pipe_exec_info);
        else if (ft_strncmp(cmd_tokens[*i], "<", 1) == 0)
                ret = handle_input_redirection(cmd_tokens, cmd_info, i);
        
        if (ret == -1)
                return (-1);
        return (0);
}
