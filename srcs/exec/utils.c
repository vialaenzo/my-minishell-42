/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:08 by eviala            #+#    #+#             */
/*   Updated: 2024/09/18 09:58:28 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("cd", cmd, 3) \
	|| !ft_strncmp("pwd", cmd, 4) || !ft_strncmp("export", cmd, 7) \
	|| !ft_strncmp("unset", cmd, 6) || !ft_strncmp("env", cmd, 4) \
	|| !ft_strncmp("exit", cmd, 5))
		return (true);
	return (false);
}

void	wait_all(t_data *data)
{
	int		status;
	int		pid;

	t_cmd *(tmp) = data->cmd;
	size_t (len) = ft_cmd_size(&tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		if (tmp->infile >= 0)
			close(tmp->infile);
		tmp = tmp->next;
	}
}
