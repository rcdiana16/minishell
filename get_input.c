/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/02/25 20:02:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_input(void)
{
	char	*line;
	char	**tokens;
	int		i;

	line = NULL;
	line = readline("$ ");
	if (!line)
		return (NULL);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (NULL);
	i = 0;
	return (tokens);
}
