/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/02/25 14:54:10 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_input()
{
	char	*line;
	size_t	size;
	char	**tokens;

	line = NULL;
	size = 0;
	printf("$");
	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	tokens = ft_split(line, ' ');
	free(line);
	return (tokens);
}
