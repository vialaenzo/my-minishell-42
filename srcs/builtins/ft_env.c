/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:39 by eviala            #+#    #+#             */
/*   Updated: 2024/09/18 10:42:33 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_liste **env, char *prefix)
{
	ft_env_sort(env);
	t_liste	(*current) = *env;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		if (prefix)
			ft_printf(1, "%s ", prefix);
		ft_printf(1, "%s\n", current->str);
		current = current->next;
	}
	return (0);
}
