/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/02/25 20:05:09 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_input(void)
{
	char	*line;
	char	**tokens;

	line = NULL;
	line = readline("$ ");
	if (!line)
		return (NULL);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}
