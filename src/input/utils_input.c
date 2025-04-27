/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:12:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/18 17:05:35 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*initialize_command(t_shell *shell)
{
	t_command	*cmd_info;

	(void)shell;
	cmd_info = NULL;
	cmd_info = malloc(sizeof(t_command));
	if (!cmd_info)
		return (NULL);
	cmd_info->c_pipe = 0;
	cmd_info->flag = 0;
	cmd_info->c_red_i = 0;
	cmd_info->here_doc = 0;
	cmd_info->c_red_o = 0;
	cmd_info->quotes_s = 0;
	cmd_info->quotes_d = 0;
	cmd_info->exit_code = 0;
	cmd_info->file_out = NULL;
	cmd_info->file_in = NULL;
	cmd_info->c_append = 0;
	cmd_info->flag_test = 0;
	cmd_info->og_stdout = dup(STDOUT_FILENO);
	cmd_info->og_stdin = dup(STDIN_FILENO);

	return (cmd_info);
}

void	handle_single_quotes(t_command *cmd_info, int i)
{
	if (cmd_info->tokens[i])
		make_good_cmd(cmd_info->tokens[i]);
}
/*
void	handle_double_quotes_and_env_vars(t_command *cmd_info, t_env *env_mini, \
	t_shell *shell, int i)
{
	char	*new_cmd;
	char	*tmp;
	int		j;

	new_cmd = make_good_cmd2(cmd_info->tokens[i]);
	if (new_cmd)
		cmd_info->tokens[i] = new_cmd;
	if (cmd_info->tokens[i][0] == '$' && cmd_info->tokens[i][1] == ' ')
		return ;
	tmp = replace_env_vars(cmd_info->tokens[i], env_mini, shell);
	if (tmp == NULL && cmd_info->c_red_o > 0)
	{
		cmd_info->flag_test = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_info->tokens[i], 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return ;
	}
	if (tmp && tmp[0] != '\0')
	{
		free(cmd_info->tokens[i]);
		cmd_info->tokens[i] = tmp;
	}
	else
	{
		free(cmd_info->tokens[i]);
		free(tmp);
		j = i;
		while (cmd_info->tokens[j])
		{
			cmd_info->tokens[j] = cmd_info->tokens[j + 1];
			j++;
		}
		cmd_info->tokens[j] = NULL;
	}
}
*/

static int	prepare_token(t_command *cmd_info, int i)
{
	char	*new_cmd;

	new_cmd = make_good_cmd2(cmd_info->tokens[i]);
	if (new_cmd)
		cmd_info->tokens[i] = new_cmd;
	if (cmd_info->tokens[i][0] == '$' && cmd_info->tokens[i][1] == ' ')
		return (0);
	return (1);
}

static int	check_ambiguous_redirect(t_command *cmd_info, char *token)
{
	if (cmd_info->c_red_o > 0)
	{
		cmd_info->flag_test = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		if (cmd_info->og_stdin != -1)
		{
			close(cmd_info->og_stdin);
			cmd_info->og_stdin = -1;
		}
		if (cmd_info->og_stdout != -1)
		{
			close(cmd_info->og_stdout);
			cmd_info->og_stdout = -1;
		}
		return (1);
	}
	return (0);
}
/*
static void	replace_or_remove_token(t_command *cmd_info, int i, char *tmp)
{
	int	j;


	if (!tmp)
	{
		
	}
	else if (tmp && tmp[0] != '\0')
	{
		free(cmd_info->tokens[i]);
		cmd_info->tokens[i] = tmp;
	}
	else
	{
		free(cmd_info->tokens[i]);
		free(tmp);
		j = i;
		while (cmd_info->tokens[j])
		{
			cmd_info->tokens[j] = cmd_info->tokens[j + 1];
			j++;
		}
		cmd_info->tokens[j] = NULL;
	}
}*/

static void replace_or_remove_token(t_command *cmd_info, int i, char *tmp)
{
    int j;

    // Si tmp est NULL (variable d'environnement non trouvée)
    if (!tmp)
    {
        free(cmd_info->tokens[i]);  // Libère le token actuel

        // Remplace le token par une chaîne vide (si tu veux qu'il n'y ait rien)
        cmd_info->tokens[i] = ft_strdup("");  // Assure-toi de dupliquer une chaîne vide
        if (!cmd_info->tokens[i])
        {
            // Si la duplication échoue, tu dois gérer l'erreur et éviter la fuite
            return;
        }
    }
    else if (tmp && tmp[0] != '\0')  // Si tmp contient une valeur valide
    {
        // Libère l'ancien token et remplace par le nouveau
        free(cmd_info->tokens[i]);
        cmd_info->tokens[i] = tmp;
    }
    else  // Si tmp est une chaîne vide (cas de remplacement vide)
    {
        free(cmd_info->tokens[i]);  // Libère l'ancien token
        free(tmp);  // Libère la chaîne vide allouée

        // Décale les autres tokens pour supprimer celui qui était à la position i
        j = i;
        while (cmd_info->tokens[j])
        {
            cmd_info->tokens[j] = cmd_info->tokens[j + 1];
            j++;
        }
        cmd_info->tokens[j] = NULL;  // Assure que la fin de la liste des tokens est bien NULL
    }
}




static void	handle_env_var_replacement(t_command *cmd_info, \
			t_env *env_mini, t_shell *shell, int i)
{
	char	*tmp;

	tmp = replace_env_vars(cmd_info->tokens[i], env_mini, shell);
	if (tmp == NULL)
	{
		if (check_ambiguous_redirect(cmd_info, cmd_info->tokens[i]))
			return ;
	}
	replace_or_remove_token(cmd_info, i, tmp);
}

void	handle_double_quotes_and_env_vars(t_command *cmd_info, \
		t_env *env_mini, t_shell *shell, int i)
{
	if (!prepare_token(cmd_info, i))
		return ;
	handle_env_var_replacement(cmd_info, env_mini, shell, i);
}

void	process_tokens(t_command *cmd_info, t_env *env_mini, t_shell *shell)
{
	int	i;

	if (!cmd_info->tokens || !cmd_info->tokens[0])
		return ;
	i = 0;
	while (cmd_info->tokens[i])
	{
		if (has_enclosed_single_quotes(cmd_info->tokens[i]))
			remove_single_quotes(cmd_info->tokens[i]);
			//handle_single_quotes(cmd_info, i);
		else
			handle_double_quotes_and_env_vars(cmd_info, env_mini, shell, i);
		i++;
	}
}
