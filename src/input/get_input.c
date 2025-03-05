/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/07 18:55:43 by maximemarti      ###   ########.fr       */
=======
/*   Updated: 2025/03/05 14:14:02 by cosmos           ###   ########.fr       */
>>>>>>> 41ae7f0 (try for parsing make good cmd)
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_redirections(char *cmd, t_command *cmd_info, int *i)
{
	if (cmd[*i] == '<')
	{
		if (cmd[*i + 1] == '<')
		{
			cmd_info->here_doc++;
			(*i)++;
		}
		else
			cmd_info->c_red_i++;
	}
	else if (cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '>')
		{
			cmd_info->c_append++;
			(*i)++;
		}
		else
			cmd_info->c_red_o++;
	}
}

void	count_special_chars(char *cmd, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			cmd_info->c_pipe++;
		else
			count_redirections(cmd, cmd_info, &i);
		i++;
	}
}

t_command	*make_good_cmd(t_command *cmd_info)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (cmd_info->tokens[i])
	{
		j = 0;
		k = 0;
		while (cmd_info->tokens[i][j])
		{
			if (cmd_info->tokens[i][j] != '\'')
<<<<<<< HEAD
			{
				cmd_info->tokens[i][k++] = cmd_info->tokens[i][j];
			}
			j++;
		}
		cmd_info->tokens[i][k] = '\0';
		cmd_info->tokens[i] = realloc(cmd_info->tokens[i], k + 1);
		i++;
	}
	return (cmd_info);
}

t_command	*make_good_cmd2(t_command *cmd_info)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (cmd_info->tokens[i])
	{
		j = 0;
		k = 0;
		while (cmd_info->tokens[i][j])
		{
			if (cmd_info->tokens[i][j] != '\"')
			{
				cmd_info->tokens[i][k++] = cmd_info->tokens[i][j];
			}
=======
				cmd_info->tokens[i][k++] = cmd_info->tokens[i][j];
>>>>>>> 41ae7f0 (try for parsing make good cmd)
			j++;
		}
		cmd_info->tokens[i][k] = '\0';
		cmd_info->tokens[i] = realloc(cmd_info->tokens[i], k + 1);
		i++;
	}
	return (cmd_info);
}

t_command	*verify_and_split_command(char *cmd, t_env *env_mini)
{
	t_command	*cmd_info;
	int			i;

	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->flag = 0;
	cmd_info->c_red_i = 0;
	cmd_info->c_red_o = 0;
	count_special_chars(cmd, cmd_info);
	cmd_info->tokens = ft_split2(cmd, " \t");
	if (cmd_info->tokens[1])
	{
		if (cmd_info->tokens[1][0] == '\'' && cmd_info->tokens[1][ft_strlen(cmd_info->tokens[1]) - 1] == '\'')
<<<<<<< HEAD
			cmd_info->flag = 1;
	}
	i = 1;
	if (cmd_info->flag != 0)
		make_good_cmd(cmd_info);
	else if (cmd_info->flag == 0)
	{
		while (cmd_info->tokens[i])
		{
			cmd_info->tokens[i] = replace_env_vars(cmd_info->tokens[i], env_mini);
			i++;
		}
		make_good_cmd2(cmd_info);
=======
			cmd_info->tokens = ft_split2(cmd, " \t\'");
		else if (cmd_info->tokens[1][0] == '\"' && cmd_info->tokens[1][ft_strlen(cmd_info->tokens[1]) - 1] == '\"')
			cmd_info->tokens = ft_split2(cmd, " \t\"");
		else
			cmd_info->tokens = ft_split2(cmd, " \t");
>>>>>>> 41ae7f0 (try for parsing make good cmd)
	}
	if (!cmd_info->tokens)
	{
		free_command(cmd_info);
		return (NULL);
	}
<<<<<<< HEAD
=======
	i = 1;
	while (cmd_info->tokens[i])
	{
		cmd_info->tokens[i] = replace_env_vars(cmd_info->tokens[i], env_mini);
		i++;
	}
	make_good_cmd(cmd_info);
>>>>>>> 41ae7f0 (try for parsing make good cmd)
	return (cmd_info);
}

t_command	*get_input(t_env *env_mini)
{
	char		*line;
	t_command	*cmd_info;

	line = readline("\033[1;32mCBS$ \033[0m");
	if (!line)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	cmd_info = verify_and_split_command(line, env_mini);
	free(line);
	return (cmd_info);
}
