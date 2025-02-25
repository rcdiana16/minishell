/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/02/25 18:38:59 by cosmos           ###   ########.fr       */
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
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	free(line);
	return (tokens);
}
