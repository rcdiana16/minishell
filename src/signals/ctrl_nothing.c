/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_nothing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:22:04 by diana             #+#    #+#             */
/*   Updated: 2025/03/11 19:48:14 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	set_gcode(131);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = handle_sigquit;
	//action.sa_mask;
	action.sa_flags = 0;
	sigaction(SIGQUIT, &action, NULL);
}
