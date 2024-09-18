/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:13 by eviala            #+#    #+#             */
/*   Updated: 2024/09/17 12:26:14 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_size_cmd(char *command, int *quotes)
{
	int (i) = 0;
	*quotes = 0;
	while (command[i] && !is_space(command[i]) && !is_special(command + i))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			(*quotes)++;
			if (command[i++] == '"')
				while (command[i] && command[i] != '"')
					++i;
			else
				while (command[i] && command[i] != '\'')
					++i;
			if (command[i])
				++i;
		}
		if (command[i] && command[i] != '"' && command[i] != '\''
			&& !is_space(command[i]) && !is_special(command + i))
			++i;
	}
	return (i);
}

static void	clear_cmd(char *command, int length, char *str, int i)
{
	int (j) = 0;
	while (command[i + j] && i < length)
	{
		if (command[i + j] == '\'' && ++j)
		{
			while (command[i + j] != '\'' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else if (command[i + j] == '"' && ++j)
		{
			while (command[i + j] != '"' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else
		{
			str[i] = command[i + j];
			i++;
		}
	}
	str[i] = 0;
}

static bool	add_cmd(t_token **begin, char **command)
{
	int	quotes;

	int (i) = 0;
	int (length) = special_size_cmd(*command, &quotes);
	if (((length) - (2 * quotes)) < 0)
		return (true);
	char *(str) = malloc(sizeof(char) * ((length + 1) - (2 * quotes)));
	if (!str)
		return (false);
	clear_cmd(*command, length - (2 * quotes), str, i);
	if (!ft_token_add_back(begin, ft_token_new(str, 0)))
		return (free(str), false);
	t_token *(token) = ft_token_last(begin);
	if ((token)->prev == NULL || (token)->prev->type == PIPE)
		(token)->type = CMD;
	else
		(token)->type = ARG;
	(*command) += length;
	return (true);
}

static bool	add_special(t_token **begin, char **command)
{
	char	*special_str;

	int (spe) = is_special(*command);
	if (!spe)
		return (false);
	if (spe == INPUT)
		special_str = ft_strdup("<");
	else if (spe == HEREDOC)
		special_str = ft_strdup("<<");
	else if (spe == TRUNC)
		special_str = ft_strdup(">");
	else if (spe == APPEND)
		special_str = ft_strdup(">>");
	else if (spe == PIPE)
		special_str = ft_strdup("|");
	else
		return (false);
	if (!special_str)
		return (false);
	if (!ft_token_add_back(begin, ft_token_new(special_str, spe)))
		return (free(special_str), false);
	if (spe == INPUT || spe == TRUNC || spe == PIPE)
		return (((*command)++), true);
	else
		return (((*command) += 2), true);
}

bool	make_tokens(t_token **begin, char *line)
{
	(*begin) = NULL;
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (*line && !is_special(line) && !add_cmd(begin, &line))
			return (ft_token_clear(begin), false);
		else if (*line && is_special(line) && !add_special(begin, &line))
			return (ft_token_clear(begin), false);
	}
	return (true);
}
