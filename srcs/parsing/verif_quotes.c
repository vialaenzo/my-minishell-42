/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:14 by eviala            #+#    #+#             */
/*   Updated: 2024/09/17 12:26:15 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_quote(bool *dq, bool *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true;
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		if (index)
			++(*index);
	}
}

int	verif_quotes(t_data *data, char *line)
{
	int (index) = 0;
	bool (sq) = false;
	bool (dq) = false;
	while (line && line[index])
	{
		which_quote(&dq, &sq, &index, line[index]);
		if (line[index] && line[index] != '\'' && line[index] != '"')
			++index;
	}
	if (dq || sq)
	{
		ft_error("Unexpected open quote ");
		data->exit_code = 2;
		return (1);
	}
	return (0);
}
