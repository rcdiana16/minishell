/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_nothing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:22:04 by diana             #+#    #+#             */
/*   Updated: 2025/03/07 17:29:03 by diana            ###   ########.fr       */
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

	action.sa_handler = handle_sigquit;
	//action.sa_mask;
	action.sa_flags = 0;
	sigaction(SIGQUIT, &action, NULL);
}
