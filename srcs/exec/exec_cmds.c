/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:25:53 by eviala            #+#    #+#             */
/*   Updated: 2024/09/20 10:51:43 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ab_path(t_data *data, char *the_cmd, t_cmd *cmd)
{
	cmd->path = ft_strdup(the_cmd);
	if (!(cmd->path))
		free_everything(data, "Alloc ab_path Failed", 1);
}

static bool	check_if_directory(t_data *data, char *the_cmd, t_cmd *cmd)
{
	struct stat	path_stat;

	if (lstat(cmd->path, &path_stat) == -1)
	{
		perror("minishell: lstat failed");
		return (data->exit_code = 126, false);
	}
	if (!S_ISREG(path_stat.st_mode) && !S_ISLNK(path_stat.st_mode))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_printf(2, "minishell: %s: Is a directory\n", the_cmd);
			return (data->exit_code = 126, false);
		}
		if (access(cmd->path, X_OK) == 0)
			return (true);
		else
		{
			ft_printf(2, "minishell: %s: Permission denied\n", the_cmd);
			return (data->exit_code = 126, false);
		}
	}
	return (true);
}

bool	is_cmd(t_data *data, t_cmd *cmd)
{
	char *(the_cmd) = cmd->cmd_param[0];
	if (ft_strchr(the_cmd, '/'))
		ab_path(data, the_cmd, cmd);
	else if (!ft_env_has("PATH", data->env) && data->path != NULL)
	{
		cmd->path = ft_strjoin(data->path, the_cmd);
		if (!cmd->path)
			return (data->exit_code = 127, false);
	}
	else if (ft_env_has("PATH", data->env))
		cmd->path = cmd_finder(data, cmd, data->env);
	else
		cmd->path = ft_strdup(the_cmd);
	if (!(cmd->path) && data->exit_code == -1)
		free_everything(data, NULL, data->exit_code);
	if (!(cmd->path))
		return (data->exit_code = 127, false);
	if (access((cmd->path), X_OK))
	{
		ft_printf(2, "minishell: %s :command not found\n", the_cmd);
		return (data->exit_code = 126, false);
	}
	if (!check_if_directory(data, the_cmd, cmd))
		return (false);
	return (true);
}
