/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:21 by eviala            #+#    #+#             */
/*   Updated: 2024/09/18 10:36:25 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int i)
{
	(void)i;
	ft_printf(1, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_pid = 130;
}

// static void	handle_quit(int i)
//{
//	(void)i;
//}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_quit(void)
{
	signal(SIGQUIT, SIG_DFL);
}
