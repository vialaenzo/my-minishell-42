/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:52 by eviala            #+#    #+#             */
/*   Updated: 2024/09/26 13:35:16 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	count_open_fds(void)
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

bool	exec_bis(t_cmd *cmd, int *pipe_fds)
{
	int (fd) = 2;
	redirect_pipe(cmd, pipe_fds);
	rl_clear_history();
	signals_quit();
	int (max_fd) = count_open_fds();
	while (++fd < max_fd)
		if (fd != cmd->infile && fd != cmd->outfile && fd != pipe_fds[1])
			close(fd);
	return (true);
}

void	child_handle_sigint(int i)
{
	(void)i;
	exit(g_signal = 130);
}

void	child_process(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	char **(env) = NULL;
	signal(SIGINT, &child_handle_sigint);
	ft_env_to_tab(&data->env, &env);
	if (!env)
		free_everything(data, "Alloc Tab_Env Failed", 1);
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0], "PARENT"))
	{
		exec_bis(cmd, pipe_fds);
		builtins_starter(data, cmd);
	}
	else if (is_cmd(data, cmd))
	{
		exec_bis(cmd, pipe_fds);
		execve(cmd->path, cmd->cmd_param, env);
	}
	ft_free_tab(env);
	free_everything(data, NULL, data->exit_code);
}
