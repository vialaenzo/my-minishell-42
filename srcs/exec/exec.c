/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:05 by eviala            #+#    #+#             */
/*   Updated: 2024/09/19 10:21:40 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	handle_parent_process(t_cmd *cmd, int *pipe_fds)
//{
//	close(pipe_fds[1]);
//	if (!cmd)
//	{
//		close(pipe_fds[0]);
//		return ;
//	}
//	if (cmd->infile >= 0)
//		close(cmd->infile);
//	if (cmd->infile == -2)
//		cmd->infile = pipe_fds[0];
//	if (cmd->next != NULL && cmd->next->infile == -2)
//		cmd->next->infile = pipe_fds[0];
//	else
//		close(pipe_fds[0]);
//}

// static bool	exec_env_cmd(t_data *data, t_cmd *cmd, int *pipe_fds)
//{
//	pid_t (pid) = fork();
//	if (pid < 0)
//		free_everything(data, "Fork failed", 1);
//	else if (pid == 0)
//	{
//		if (cmd && cmd->cmd_param && cmd->cmd_param[0])
//			child_process(data, cmd, pipe_fds);
//		else
//			free_everything(data, NULL, 0);
//	}
//	else
//		handle_parent_process(cmd, pipe_fds);
//	return (true);
//}

static void	handle_parent_process(t_cmd *cmd, int *pipe_fds)
{
	close(pipe_fds[1]);
	if (!cmd)
	{
		close(pipe_fds[0]);
		return ;
	}
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	if (cmd->infile == -2)
		cmd->infile = pipe_fds[0];
	else if (cmd->next != NULL && cmd->next->infile == -2)
		cmd->next->infile = pipe_fds[0];
	else
		close(pipe_fds[0]);
}

static bool	exec_env_cmd(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	pid_t (pid) = fork();
	if (pid < 0)
		free_everything(data, "Fork failed", 1);
	else if (pid == 0)
	{
		close(pipe_fds[0]);
		if (cmd && cmd->cmd_param && cmd->cmd_param[0])
			child_process(data, cmd, pipe_fds);
		else
			free_everything(data, NULL, 0);
	}
	else
		handle_parent_process(cmd, pipe_fds);
	return (true);
}

bool	exec(t_data *data)
{
	if (!data || (!data->cmd))
		return (false);
	int *(pip) = data->pipe;
	t_cmd *(tmp) = data->cmd;
	if (tmp && tmp->skip_cmd == false && !tmp->next && tmp->cmd_param[0]
		&& is_builtin(tmp->cmd_param[0]))
		return (builtins_starter(data, tmp));
	if (pipe(pip) == -1)
		return (false);
	exec_env_cmd(data, tmp, pip);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (pipe(pip) == -1)
			return (true);
		exec_env_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}
