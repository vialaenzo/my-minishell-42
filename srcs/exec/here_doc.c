/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:04:23 by eviala            #+#    #+#             */
/*   Updated: 2024/09/24 14:37:56 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint_child(int signum)
{
	if (signum == SIGINT)
		exit(130);
}

static bool	read_heredoc(t_data *data, char *limiter)
{
	char	*buf;
	int		fd;

	signal(SIGINT, &handle_sigint_child);
	while (1)
	{
		buf = readline("\033[1;93mheredoc>\033[0m ");
		if (!buf)
		{
			ft_printf(2, "minishell: warning: here-document at line 1 delimited"
				" by end-of-file (wanted '%s')\n", limiter);
			break ;
		}
		if (ft_strncmp(limiter, buf, ft_strlen(limiter) + 1) == 0)
			return (free(buf), true);
		if (!ft_expand(&buf, data))
			return (free(buf), false);
		fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (ft_error("Failed to create temp file"), -1);
		ft_printf(fd, "%s\n", buf);
		close(fd);
		free(buf);
	}
	return (true);
}

int	here_doc(t_data *data, char *limiter)
{
	int		status;

	pid_t (pid) = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (!read_heredoc(data, limiter))
			free_everything(data, "Erreur expand", 1);
		free_everything_heredoc(data, NULL, 0);
	}
	waitpid(pid, &status, 0);
	g_signal = WEXITSTATUS(status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (unlink(".heredoc.tmp"), -1);
	int (fd) = open(".heredoc.tmp", O_RDONLY);
	if (fd < 0)
		return (unlink(".heredoc.tmp"), -1);
	unlink(".heredoc.tmp");
	return (fd);
}
