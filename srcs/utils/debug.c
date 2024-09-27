/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:15 by eviala            #+#    #+#             */
/*   Updated: 2024/09/24 14:41:46 by dtrala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*type_to_str(t_type type)
{
	if (type == INPUT)
		return ("INPUT");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == TRUNC)
		return ("TRUNC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == CMD)
		return ("CMD");
	else if (type == ARG)
		return ("ARG");
	else
		return ("UNKNOWN");
}

void	token_display(t_token *token)
{
	t_token *(current) = token;
	while (current)
	{
		ft_printf(1, "Type> [%d] : %s, %s\n", current->type,
			type_to_str(current->type), current->str);
		current = current->next;
	}
}

bool	test_token(t_data *data, char *line)
{
	if (!make_tokens(&data->token, line) || data->token == NULL)
		return (ft_error("Aie coup dur"), false);
	token_display(data->token);
	ft_printf(2, "it's ok\n");
	return (true);
}

void	cmd_display(t_cmd *cmd)
{
	int (i) = 0;
	while (cmd->prev)
		cmd = cmd->prev;
	t_cmd *(current) = cmd;
	while (current)
	{
		ft_printf(2, "CMD : |%s| | Infile : %d | Outfile %d | Skip : %d\n",
			current->cmd_param[0], current->infile,
			current->outfile, current->skip_cmd);
		ft_printf(2, "Liste des params : \n");
		i = -1;
		while (current->cmd_param[++i])
			ft_printf(2, "%s\n", current->cmd_param[i]);
		ft_printf(2, "\n");
		current = current->next;
	}
}

bool	test_cmds(t_data *data)
{
	ft_printf(2, "test cmds\n");
	if (!make_cmds(data) || data->cmd == NULL)
		return (ft_error("Aie coup dur cmd"), false);
	cmd_display(data->cmd);
	return (true);
}
