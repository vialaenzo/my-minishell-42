/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:03 by eviala            #+#    #+#             */
/*   Updated: 2024/09/20 10:30:26 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strjoin_slash(char *dest, char *str, char *env, int *index)
{
	int(i) = 0;
	while (*index < (PATH_MAX - 1) && env[(*index)] && env[(*index)] != ':')
		dest[i++] = env[(*index)++];
	++(*index);
	dest[i++] = '/';
	int(j) = 0;
	while (j < (PATH_MAX - 1) && str[j])
		dest[i++] = str[j++];
	dest[i] = '\0';
	return (0);
}

static char	*create_paths(t_liste *env, int len)
{
	t_liste *(tmp) = env;
	while (len--)
	{
		if (ft_strncmp(tmp->str, "PATH=", 5) == 0)
			return (&(tmp->str[5]));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*cmd_finder(t_data *data, t_cmd *cmd, t_liste *env)
{
	char	path[PATH_MAX];

	ft_printf(2, "cmd finder\n");
	char *(the_cmd) = cmd->cmd_param[0];
	if (!the_cmd || the_cmd[0] == '\0')
		return (ft_printf(2, "minishell: : command not found\n"), NULL);
	char *(paths) = create_paths(env, ft_liste_size(&env));
	if (!paths || ft_strlen(the_cmd) > PATH_MAX / 2)
		return (ft_printf(2, "minishell: %s : command not found\n",
		the_cmd),NULL);
	int (i) = 0;
	int (len) = ft_strlen(paths);
	while (i < len)
	{
		ft_strjoin_slash(path, the_cmd, paths, &i);
		if (access(path, F_OK) == 0)
		{
			the_cmd = ft_strdup(path);
			if (!the_cmd)
			{
				ft_error("Alloc the_cmd failed");
				data->exit_code = -1;
			}
			return (the_cmd);
		}
	}
	return (ft_printf(2, "minishell: %s : command not found\n", the_cmd), NULL);
}
