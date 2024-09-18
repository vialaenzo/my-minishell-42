/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_center.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:10 by eviala            #+#    #+#             */
/*   Updated: 2024/09/18 13:48:10 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	choice_file(t_data *data, char *filename, int type)
{
	int (fd) = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = here_doc(data, filename);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

static bool	get_in(t_data *data, t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == INPUT || tmp->type == HEREDOC)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp->next == NULL || tmp->next->type <= 5)
			return (error_token(tmp));
		cmd->infile = choice_file(data, tmp->next->str, tmp->type);
		if (cmd->infile == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token *(tmp) = token;
	if (tmp->type != PIPE && !get_in(data, tmp, cmd))
		return (false);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (!get_in(data, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

static bool	get_out(t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == TRUNC || tmp->type == APPEND)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp->next == NULL || tmp->next->type <= 5)
			return (error_token(tmp));
		cmd->outfile = choice_file(NULL, tmp->next->str, tmp->type);
		if (cmd->outfile == -1)
			return (false);
	}
	return (true);
}

bool	get_outfile(t_token *token, t_cmd *cmd)
{
	t_token *(tmp) = token;
	if (tmp->type != PIPE && !get_out(tmp, cmd))
		return (false);
	tmp = tmp->next;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (!get_out(tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
