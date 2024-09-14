#include "minishell.h"

static void	handle_parent_process(t_cmd *cmd, int *pipe_fds)
{
	close(pipe_fds[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = pipe_fds[0];
	if (cmd->next != NULL && cmd->next->infile == -2)
		cmd->next->infile = pipe_fds[0];
	else
		close(pipe_fds[0]);
}

static bool	exec_env_cmd(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	g_pid = fork();
	if (g_pid < 0)
		free_everything(data, "Fork failed", 1);
	else if (!g_pid)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(data, cmd, pipe_fds);
		else
			free_everything(data, NULL, 0);
	}
		handle_parent_process(cmd, pipe_fds);
	return (true);
}

bool	exec(t_data *data)
{
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
			return (-1);
		exec_env_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}
