/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:13:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/03/27 15:15:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
char	**get_tokens(char *cmd)
{
	char	**tokens;

	tokens = ft_split(cmd, ' ');
	return (tokens);
}*/



char **get_tokens(char *cmd)
{
    char **tokens;
    int equal_count = 0;
    char *ptr = cmd;
    char *first_equal;

    // Count how many '=' characters are in the command
    while (*ptr)
    {
        if (*ptr == '=')
            equal_count++;
        ptr++;
    }

    // If there is exactly one '=', split by '='
    if (equal_count == 1)
    {
        tokens = ft_split(cmd, '=');
    }
    else if (equal_count > 1)
    {
        // If there is more than one '=', split by first '='
        first_equal = strchr(cmd, '=');  // Find the first '='
        *first_equal = '\0';  // Temporarily terminate the string at the first '='

        // Split the part before the first '='
        tokens = ft_split(cmd, ' ');
        
        // Now handle the part after the first '=' (split by spaces)
        char *rest = first_equal + 1;  // Part after the first '='
        char **rest_tokens = ft_split(rest, ' ');
        
        // Append the rest tokens to the original tokens
        int i = 0, j = 0;
        while (tokens[i]) i++;  // Find the end of the tokens array
        while (rest_tokens[j])   // Append the rest_tokens
        {
            tokens[i] = rest_tokens[j];
            i++;
            j++;
        }
        tokens[i] = NULL;  // Null terminate the tokens array

        free(rest_tokens);  // Clean up the rest_tokens array
    }
    else
    {
        // If no '=', just split by space
        tokens = ft_split(cmd, ' ');
    }

    return tokens;
}



void	join_cmd_values(char **cmd, char **value)
{
	char	*temp;

	if (!cmd || !cmd[1])
		return ;
	if (cmd[0][0] == '\"' || cmd[0][0] == '\'')
	{
		temp = ft_strjoin(*value, " ");
		*value = ft_strjoin(temp, cmd[1]);
		free(temp);
	}
	else
		*value = ft_strdup(cmd[1]);
}

