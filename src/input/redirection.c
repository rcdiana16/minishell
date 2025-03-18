#include "../../include/minishell.h"

void	count_input_redirections(char *cmd, t_command *cmd_info, int *i)
{
	if (cmd[*i] == '<')
	{
		if (cmd[*i + 1] == '<')
		{
			cmd_info->here_doc++;
			(*i)++;
		}
		else
			cmd_info->c_red_i++;
	}
}

void	count_output_redirections(char *cmd, t_command *cmd_info, int *i)
{
	if (cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '>')
		{
			cmd_info->c_append++;
			(*i)++;
		}
		else
			cmd_info->c_red_o++;
	}
	else if (cmd[*i] == '|' && ft_strlen(cmd) == 1)
		cmd_info->c_pipe++;
}

void	count_redirections(char *cmd, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		count_input_redirections(cmd, cmd_info, &i);
		count_output_redirections(cmd, cmd_info, &i);
		i++;
	}
}

