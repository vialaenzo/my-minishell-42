/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:06 by eviala            #+#    #+#             */
/*   Updated: 2024/09/18 09:53:19 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	read_heredoc(t_data *data, int fd, char *limiter)
{
	char *(buf) = NULL;
	while (1)
	{
		buf = readline("\033[1;93mheredoc>\033[0m ");
		if (!buf)
		{
			ft_error("Buf readline");
			break ;
		}
		
		if ((ft_strncmp(limiter, buf, ft_strlen(limiter)+1) == 0))
			break ;
		if (!ft_expand(&buf, data))
			free_everything(data, "Allocation failed", 1);
		ft_printf(fd, "%s\n", buf);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

int	here_doc(t_data *data, char *limiter)
{
	int (fd) = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_heredoc(data, fd, limiter))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
