/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:23 by eviala            #+#    #+#             */
/*   Updated: 2024/09/25 13:49:45 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_error(char *str)
{
	if (str)
		ft_printf(2, "minishell: %s\n", str);
	return (false);
}

int	is_special(char *str)
{
	if (str && *str && ft_strlen(str) >= 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(str, ">>", 2))
			return (APPEND);
	}
	if (str && *str && ft_strlen(str) >= 1)
	{
		if (!ft_strncmp(str, "<", 1))
			return (INPUT);
		if (!ft_strncmp(str, ">", 1))
			return (TRUNC);
		if (!ft_strncmp(str, "|", 1))
			return (PIPE);
	}
	return (0);
}

bool	check_is_pipe(t_data *data)
{
	t_token *(tmp) = data->token;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if ((!tmp->next && tmp->type == PIPE)
			|| (!tmp->prev && tmp->type == PIPE) || (tmp->next
				&& tmp->type == PIPE && tmp->next->type == PIPE))
		{
			ft_error("Syntax error unexpected '|' token");
			ft_token_clear(&data->token);
			ft_cmd_clear(&data->cmd);
			return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t'
			|| c == '\v'))
		return (true);
	return (false);
}

bool	invalid_line(char *line)
{
	size_t (i) = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}
