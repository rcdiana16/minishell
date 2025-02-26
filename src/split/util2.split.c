/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:41:22 by cosmos            #+#    #+#             */
/*   Updated: 2025/02/26 17:12:11 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**allocate_array(int word_count)
{
	return (calloc((word_count + 1), sizeof(char *)));
}

void	add_word_to_result(char **res, int j, char *word)
{
	res[j] = word;
	if (!res[j])
		free_array(res, j);
}
