/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:52 by eviala            #+#    #+#             */
/*   Updated: 2024/09/17 12:25:53 by eviala           ###   ########.fr       */
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

static void	run_built(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	close(pipe_fds[0]);
	if (cmd->outfile < 0 && cmd->next != NULL)
		cmd->outfile = pipe_fds[1];
	else
		close(pipe_fds[1]);
	builtins_starter(data, cmd);
}

void	child_process(t_data *data, t_cmd *cmd, int *pipe_fds)
{
	char **(env) = NULL;
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
		execve(cmd->path, cmd->cmd_param, env);
		free(env);
	}
	free_everything(data, NULL, data->exit_code);
}
