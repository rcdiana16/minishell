/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:42 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/05 16:54:42 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_exit_argument_error(t_command *cmd_info)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	cmd_info->exit_code = 1;
}

int	validate_exit_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_cleanup(t_env *env_mini, t_command *cmd_info, char **path)
{
	free_env_list(env_mini);
	free_command(cmd_info);
	free_arr(path);
	close(0);
	close(1);
	close(2);
}

static void	exit_with_error(t_env *env_mini, t_command *cmd_info, \
							char **path, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	close_fd(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit(2);
}
/*
int	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, char **path)
{
	long long	ex;
	int			i;

	i = 0;
	ex = 0;
	get_next_line(-42);
	while (cmd[i])
		i++;
	if (cmd[1])
	{
		if (!validate_exit_argument(cmd[1]))
			exit_with_error(env_mini, cmd_info, path, cmd[1]);
		else if (i > 2)
		{
			handle_exit_argument_error(cmd_info);
			return (1);
		}
		else
			ex = ft_atoll(cmd[1]);
	}
	else
		ex = cmd_info->exit_code;
	close_fd(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit((unsigned char)ex);
	return (0);
}
*/

static int	handle_exit_args(char **cmd, t_command *cmd_info, \
	t_env *env_mini, char **path)
{
	long long	ex;
	int			count;

	count = 0;
	ex = 0;
	while (cmd[count])
		count++;
	if (cmd[1])
	{
		if (!validate_exit_argument(cmd[1]))
			exit_with_error(env_mini, cmd_info, path, cmd[1]);
		else if (count > 2)
		{
			handle_exit_argument_error(cmd_info);
			return (-1);
		}
		ex = ft_atoll(cmd[1]);
	}
	else
		ex = cmd_info->exit_code;
	return ((unsigned char)ex);
}

static void	cleanup_and_exit(t_env *env_mini, t_command *cmd_info, \
	char **path, int ex)
{
	close_fd(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit(ex);
}

int	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, char **path)
{
	int	ex;

	get_next_line(-42);
	ex = handle_exit_args(cmd, cmd_info, env_mini, path);
	if (ex == -1)
		return (1);
	cleanup_and_exit(env_mini, cmd_info, path, ex);
	return (0);
}
