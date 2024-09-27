/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:08 by eviala            #+#    #+#             */
/*   Updated: 2024/09/25 13:49:02 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd, char *TYPE)
{
	if (!cmd)
		return (false);
	if (!TYPE)
		return (false);
	if (ft_strncmp(TYPE, "CHILD", 6) || ft_strncmp(TYPE, "PARENT", 7))
		if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("pwd", cmd, 4)
			|| !ft_strncmp("env", cmd, 4))
			return (true);
	if (ft_strncmp(TYPE, "ALONE", 6) || ft_strncmp(TYPE, "PARENT", 7))
		if (!ft_strncmp("cd", cmd, 3) || !ft_strncmp("export", cmd, 7)
			|| !ft_strncmp("unset", cmd, 6) || !ft_strncmp("exit", cmd, 5))
			return (true);
	return (false);
}

void	wait_all(t_data *data)
{
	int	status;
	int	pid;

	t_cmd *(tmp) = data->cmd;
	size_t(len) = ft_cmd_size(&tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid != 0)
			if (WIFEXITED(status) && pid == data->last_pid)
				data->exit_code = WEXITSTATUS(status);
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		if (tmp->infile >= 0)
			close(tmp->infile);
		tmp = tmp->next;
	}
}
