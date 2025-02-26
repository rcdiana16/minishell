/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:54:37 by diana             #+#    #+#             */
/*   Updated: 2025/02/26 17:11:56 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int	verify_tokens(char **cmd)
{
	int	i;
	int	c_pipe;
	int	c_red_i;
	int	c_red_o;

	i = 0;
	c_red_i = 0;
	c_red_o = 0;
	while (cmd[i])
	{
		if ()
		i++;
	}
}
*/
char	**get_input(void)
{
	char	*line;
	char	**tokens;
	//char	**tokens2;

	line = NULL;
	line = readline("$ ");
	if (!line)
		return (NULL);
	tokens = ft_split2(line, " |\t/&");
	//verify_tokens(tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}
