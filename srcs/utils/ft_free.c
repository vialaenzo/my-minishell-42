/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:19 by eviala            #+#    #+#             */
/*   Updated: 2024/09/23 13:48:18 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_everything(t_data *data, char *err, int ext)
{
	if (data->cmd)
		ft_cmd_clear(&data->cmd);
	if (data->token)
		ft_token_clear(&data->token);
	if (data->env)
		ft_liste_clear(&data->env);
	if (data->export)
		ft_liste_clear(&data->export);
	if (data->pipe[0] && data->pipe[0] != -1)
		close(data->pipe[0]);
	if (data->pipe[1] && data->pipe[1] != -1)
		close(data->pipe[1]);
	if (err)
		ft_error(err);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
		exit(ext);
}

void	free_everything_heredoc(t_data *data, char *err, int ext)
{
	if (data->cmd)
		ft_cmd_clear(&data->cmd);
	if (data->token)
		ft_token_clear(&data->token);
	if (data->env)
		ft_liste_clear(&data->env);
	if (data->export)
		ft_liste_clear(&data->export);
	if (data->pipe[0] && data->pipe[0] != -1)
		close(data->pipe[0]);
	if (data->pipe[1] && data->pipe[1] != -1)
		close(data->pipe[1]);
	if (err)
		ft_error(err);
	rl_clear_history();
	if (ext != -1)
		exit(ext);
}
