/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_starter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:47 by eviala            #+#    #+#             */
/*   Updated: 2024/09/18 11:14:29 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(int save_stdout, t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd_param[0], 5))
		data->exit_code = ft_echo(cmd->cmd_param);
	else if (!ft_strncmp("cd", cmd->cmd_param[0], 3))
		data->exit_code = ft_cd(data, cmd->cmd_param);
	else if (!ft_strncmp("pwd", cmd->cmd_param[0], 4))
		data->exit_code = ft_pwd(cmd->cmd_param);
	else if (!ft_strncmp("export", cmd->cmd_param[0], 7))
		data->exit_code = ft_export(data, cmd->cmd_param);
	else if (!ft_strncmp("unset", cmd->cmd_param[0], 6))
		data->exit_code = ft_unset(data, cmd->cmd_param);
	else if (!ft_strncmp("env", cmd->cmd_param[0], 4))
		data->exit_code = ft_env(&data->env, NULL);
	else if (!ft_strncmp("exit", cmd->cmd_param[0], 5))
	{
		if (cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(data, cmd->cmd_param);
	}
}

bool	builtins_starter(t_data *data, t_cmd *cmd)
{
	int (stdout_copy) = -1;
	if (cmd->outfile >= 0)
	{
		stdout_copy = dup(1);
		dup2(cmd->outfile, 1);
	}
	exec_builtin(stdout_copy, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(stdout_copy, 1);
		close(stdout_copy);
	}
	return (true);
}
