#include "minishell.h"

static void	handle_sigint(int i)
{
	(void)i;
	ft_printf(1, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_pid == 0)
		rl_redisplay();
}

//static void	handle_quit(int i)
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
