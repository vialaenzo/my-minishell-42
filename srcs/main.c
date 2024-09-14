#include "minishell.h"

pid_t		g_pid;

void	init_data(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_pid = 0;
	data->env = NULL;
	data->export = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	signals();
}

static bool	ft_parse(t_data *data, char *line)
{
	if ((line[0] == '\"' && line[0] == '\"')
		|| (line[0] == '\'' && line[0] == '\''))
		return (ft_error("asdf : command not found"), free(line), false);
	if (verif_quotes(data, line))
		return (free(line), false);
	if ((ft_expand(&line, data)) && (!make_tokens(&data->token, line)))
		return (free(line),
			free_everything(data, "Make token error", 1), false);
	token_display(data->token);
	free(line);
	if (data->token && (ft_token_last(&data->token)->type == PIPE)
		&& ft_token_size(&data->token) != 1
		&& !(ft_token_last(&data->token)->prev->type == PIPE))
	{
		ft_error("Unclosed Pipe");
		data->exit_code = 2;
		return (ft_token_clear(&data->token), false);
	}
	if (!check_is_pipe(data))
		return (false);
	if (!data->token || !make_cmds(data))
		return (ft_token_clear(&data->token), ft_cmd_clear(&data->cmd), false);
	return (true);
}

int	ft_env_copy(t_data *data, char **env)
{
	int	i;

	if (!env || !env[0])
		return (0);
	i = -1;
	while (env[++i])
	{
		if(ft_export_one(&data->env, &data->export, env[i]))
			return (ft_liste_clear(&data->env), ft_liste_clear(&data->export), 0);
	}
	return (1);
}
static void	ft_start(t_data *data)
{
	if (!exec(data))
		free_everything(data, "Pipe error", 1);
	ft_cmd_clear(&data->cmd);
	ft_token_clear(&data->token);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	char *(line) = NULL;
	init_data(&data, argc, argv);
	if (!ft_env_new(&data) || !ft_env_copy(&data, env))
		return (free_everything(&data, "Env Failed", -1), 1);
	while (true)
	{
		line = readline("\033[0;35mminishell>\033[0m ");
		if (!line)
			free_everything(&data, "exit", data.exit_code);
		if ((empty_line(line)))
			continue ;
		add_history(line);
		if (!ft_parse(&data, line))
			continue ;
		ft_start(&data);
		g_pid = 0;
	}
	rl_clear_history();
	free_everything(&data, NULL, -1);
	return (0);
}
