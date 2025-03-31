/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:42 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/31 16:20:32 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
void	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, \
		char **path)
{
	int	ex;
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		cmd_info->exit_code = 2;
		return ;
	}
	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				cmd_info->exit_code = 2;
				return ;
			}
			i++;
		}
	}
	ex = 0;
	if (cmd[1])
		ex = ft_atoi(cmd[1]);
	free_env_list(env_mini);
	free_command(cmd_info);
	free_arr(path);
	exit (ex);
}*/

void	handle_exit_argument_error(t_command *cmd_info)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	cmd_info->exit_code = 2;
}

int	validate_exit_argument(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_our_exit(t_env *env_mini, char **cmd, t_command *cmd_info, \
		char **path)
{
	int	ex;
	int	i;

	ex = 0;
	i = 0;
	while (cmd[i])
		i++;
	if (i >= 3)
	{
		handle_exit_argument_error(cmd_info);
		return ;
	}
	if (cmd[1] && !validate_exit_argument(cmd[1]))
	{
		cmd_info->exit_code = 2;
		return ;
	}
	if (cmd[1])
		ex = ft_atoi(cmd[1]);
	free_env_list(env_mini);
	free_command(cmd_info);
	free_arr(path);
	exit(ex);
}
