/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:52 by eviala            #+#    #+#             */
/*   Updated: 2024/09/20 09:27:22 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static void	redirect_pipe(t_cmd *cmd, int *pipe_fds)
{
	close(pipe_fds[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != NULL)
		dup2(pipe_fds[1], 1);
	close(pipe_fds[1]);
}

static void	run_built(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	close(pipe_fds[0]);
	if (cmd->outfile < 0 && cmd->next != NULL)
		cmd->outfile = pipe_fds[1];
	else
		close(pipe_fds[1]);
	builtins_starter(data, cmd);
}

int	count_open_fds(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir("/proc/self/fd");
	if (!dir)
	{
		perror("opendir");
		return (-1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

void	child_process(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	int	max_fd;

	int (fd) = 2;
	char (**env) = NULL;
	signal(SIGINT, SIG_IGN);
	ft_env_to_tab(&data->env, &env);
	if (!env)
		free_everything(data, "Alloc Tab_Env Failed", 1);
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		run_built(data, cmd, pipe_fds);
	else if (is_cmd(data, cmd))
	{
		redirect_pipe(cmd, pipe_fds);
		rl_clear_history();
		signals_quit();
		max_fd = count_open_fds();
		while (++fd < max_fd)
			if (fd != cmd->infile && fd != cmd->outfile && fd != pipe_fds[1])
				close(fd);
		execve(cmd->path, cmd->cmd_param, env);
		free(env);
	}
	free_everything(data, NULL, data->exit_code);
}
