/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:35:08 by diana             #+#    #+#             */
/*   Updated: 2025/03/07 18:34:47 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	set_gcode(1);
}

void	sigint(void)
{
	struct sigaction	action;

	action.sa_handler = &handle_sigint;
	sigaction(SIGINT, &action, NULL);
}

void	set_signals(void)
{
	sigint();
}
