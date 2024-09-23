/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:39 by eviala            #+#    #+#             */
/*   Updated: 2024/09/20 17:24:26 by dtrala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_liste **env, char *prefix)
{
	t_liste	*current;

	ft_env_sort(env);
	current = *env;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		if (prefix && (ft_strncmp(current->str, "_\0", 2) == 0))
		{
			current = current->next;
			continue;
		}
		if (prefix && (ft_strncmp(current->str, "_=", 2) == 0))
		{
			current = current->next;
			continue;
		}
		if (prefix)
			ft_printf(1, "%s ", prefix);
		ft_printf(1, "%s\n", current->str);
		current = current->next;
	}
	return (0);
}
