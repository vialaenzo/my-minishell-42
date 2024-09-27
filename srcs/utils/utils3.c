/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:31:52 by eviala            #+#    #+#             */
/*   Updated: 2024/09/24 15:23:40 by dtrala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_has(t_token *token, t_type TYPE)
{
	if (!token)
		return (0);
	t_token *(tmp) = token;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == TYPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export_last_arg(t_data *data)
{
	if (ft_token_has(data->token, PIPE))
		return (0);
	char *(value) = NULL;
	if (!data || !data->token)
		return (0);
	t_token *(curr) = ft_token_last(&data->token);
	value = ft_strjoin("_=", curr->str);
	if (!value)
		return (0);
	ft_export_one(&data->env, &data->export, value);
	free(value);
	return (1);
}
