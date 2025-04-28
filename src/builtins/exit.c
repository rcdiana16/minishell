/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:42 by cosmos            #+#    #+#             */
/*   Updated: 2025/04/27 21:17:20 by diana            ###   ########.fr       */
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

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static void	close_original_fds(t_command *cmd_info)
{
	if (cmd_info->og_stdin != -1)
	{
		close(cmd_info->og_stdin);
		cmd_info->og_stdin = -1;
	}
	if (cmd_info->og_stdout != -1)
	{
		close(cmd_info->og_stdout);
		cmd_info->og_stdout = -1;
	}
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
	close_original_fds(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit(2);
}

int	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, char **path)
{
	long long	ex;
	int			i;

	i = 0;
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
	close_original_fds(cmd_info);
	exit_cleanup(env_mini, cmd_info, path);
	exit((unsigned char)ex);
	return (0);
}
