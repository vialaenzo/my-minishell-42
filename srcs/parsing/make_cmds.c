#include "minishell.h"

static bool	fill_cmd(t_data *data, t_token *tmp)
{
	t_cmd *(cmd_ac) = ft_cmd_last(&data->cmd);
	if (!get_infile(data, tmp, cmd_ac) && cmd_ac->infile != -1)
		return (false);
	if (cmd_ac->infile == -1)
	{
		cmd_ac->skip_cmd = true;
		cmd_ac->outfile = -1;
		return (true);
	}
	if (!get_outfile(tmp, cmd_ac) && cmd_ac->outfile != -1)
		return (false);
	if (cmd_ac->outfile == -1)
	{
		if (cmd_ac->infile >= 0)
			close(cmd_ac->infile);
		cmd_ac->skip_cmd = true;
		cmd_ac->infile = -1;
		return (true);
	}
	cmd_ac->cmd_param = get_param(data, tmp);
	if (!cmd_ac->cmd_param)
		free_everything(data, "Allocation failed param", 1);
	return (true);
}

static bool	cmd_maker(t_data *data, t_token *tmp)
{
	if (!ft_cmd_add_back(&data->cmd, ft_cmd_new(-2, -2, NULL)))
		free_everything(data, "Allocation failed cmd_maker", 1);
	if (!fill_cmd(data, tmp))
		return (data->exit_code = 2, false);
	return (true);
}

bool	make_cmds(t_data *data)
{
	t_token *(tmp) = data->token;
	if (!cmd_maker(data, tmp))
		return (false);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (tmp->prev && tmp->prev->type == PIPE)
		{
			if (!cmd_maker(data, tmp))
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
