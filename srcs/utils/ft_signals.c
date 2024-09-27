/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:21 by eviala            #+#    #+#             */
/*   Updated: 2024/09/27 12:37:09 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_exec(int i)
{
	(void)i;
	ft_printf(1, "\n");
	g_signal = 130;
}

static void	handle_sigint(int i)
{
	(void)i;
	ft_printf(1, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 130;
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_quit(void)
{
	signal(SIGQUIT, SIG_DFL);
}
