/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:37:48 by diana             #+#    #+#             */
/*   Updated: 2025/03/07 17:30:01 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	backslash_n(int v)
{
	(void)v;
	write(1, "\n", 1);
	rl_redisplay();
}

void	sigint_update(void)
{
	struct sigaction	action;

	action.sa_handler = &backslash_n;
	sigaction(SIGINT, &action, NULL);
}

void	nothing(int v)
{
	(void)v;
	ft_putstr_fd("Quit: 3\n", 1);
	rl_redisplay();
}

void	sigquit_update(void)
{
	struct sigaction	action;

	action.sa_handler = &nothing;
	sigaction(SIGQUIT, &action, NULL);
}
