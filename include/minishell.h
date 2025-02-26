/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:46:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/02/26 17:11:00 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_split_data
{
	char		**res;
	int			*j;
	int			*s_word;
	const char	*delimiters;
	const char	*s;
}	t_split_data;

//path.c
char	**get_path(void);
char	**split_path(char *path);
//get_input.c
char	**get_input(void);
//split_bis.c
char	**ft_split2(const char *s, const char *delimiters);
//utils_split.c
bool	is_delimiter(char c, const char *delimiters);
void	initialize_vars(int *j, int *s_word);
int		get_end(const char *s, size_t i, const char *delimiters);
void	free_array(char **strs, int count);
char	*create_word(const char *str, int start, int end);
//utils2_split.c
char	**allocate_array(int word_count);
void	add_word_to_result(char **res, int j, char *word);

#endif