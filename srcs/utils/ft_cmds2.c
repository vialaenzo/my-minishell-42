/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:17 by eviala            #+#    #+#             */
/*   Updated: 2024/09/17 12:26:18 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_cmd_size(t_cmd **cmd)
{
	t_cmd *(current) = *cmd;
	if (!current)
		return (0);
	while (current->prev)
		current = current->prev;
	size_t (size) = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
