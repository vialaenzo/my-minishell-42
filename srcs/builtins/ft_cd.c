/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:24:54 by eviala            #+#    #+#             */
/*   Updated: 2024/09/17 12:24:55 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_old_new_pwd(char **old, char **new, t_liste **env)
{
	char *(old_value) = NULL;
	char *(cwd) = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	if (!ft_env_get("PWD", &old_value, *env))
		return (0);
	*old = ft_strjoin("OLDPWD=", old_value);
	free(old_value);
	if (!old)
		return (0);
	*new = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!*new)
		return (free(*old), 0);
	return (1);
}

static int	ft_cd_to_old(t_data *data, char **args)
{
	char *(old) = NULL;
	char *(pwd) = NULL;
	char *(old_entry) = NULL;
	char *(pwd_entry) = NULL;
	if (!ft_env_get("OLDPWD", &old, data->env))
		return (1);
	if (!ft_env_get("PWD", &pwd, data->env))
		return (free(old), 1);
	if (chdir(old) != 0)
		return (free(old), free(pwd), 1);
	old_entry = ft_strjoin("OLDPWD=", pwd);
	if (!old_entry)
		return (free(old), free(pwd), 1);
	pwd_entry = ft_strjoin("PWD=", old);
	if (!pwd_entry)
		return (free(old), free(pwd), free(old_entry), 1);
	if (ft_export_one(&data->env, &data->export, pwd_entry) != 0)
		return (free(old), free(pwd), free(old_entry), free(pwd_entry), 1);
	if (ft_export_one(&data->env, &data->export, old_entry) != 0)
		return (free(old), free(pwd), free(old_entry), free(pwd_entry), 1);
	ft_pwd(args);
	return (free(old), free(pwd), free(old_entry), free(pwd_entry), 0);
}

static int	ft_cd_home(t_data *data, char **args)
{
	char *(home) = NULL;
	char *(old_pwd) = NULL;
	char *(new_pwd) = NULL;
	(void)args;
	if (!ft_env_get("HOME", &home, data->env))
		return (free(home), ft_printf(2, "minishell: cd: HOME not set\n"), 1);
	if (chdir(home) != 0)
		return (free(home), 1);
	free(home);
	if (!ft_get_old_new_pwd(&old_pwd, &new_pwd, &data->env))
		return (1);
	if (ft_export_one(&data->env, &data->export, old_pwd) != 0)
		return (0);
	free(old_pwd);
	if (ft_export_one(&data->env, &data->export, new_pwd) != 0)
		return (free(new_pwd), 1);
	return (free(new_pwd), 0);
}

int	ft_cd(t_data *data, char **args)
{
	char *(old_pwd) = NULL;
	char *(new_pwd) = NULL;
	if (!args)
		return (1);
	if (ft_size_tab(args) == 1)
		return (ft_cd_home(data, args));
	if (ft_size_tab(args) > 2)
		return (ft_printf(2, "minishell: cd: too many arguments\n", args[1]),
			1);
	if (ft_strlen(args[1]) && ft_strnstr(args[1], "--", 2))
		return (ft_cd_to_old(data, args), ft_cd_home(data, args));
	if (ft_strlen(args[1]) && args[1][0] == '-' && args[1][1] == '\0')
		return (ft_cd_to_old(data, args));
	if (ft_strlen(args[1]) && args[1][0] == '~' && args[1][1] == '\0')
		return (ft_cd_home(data, args));
	if (chdir(args[1]) != 0 && args[1])
		return (ft_printf(2, "minishell: cd: %s: No such file or directory\n",
				args[1]), 1);
	if (!ft_get_old_new_pwd(&old_pwd, &new_pwd, &data->env))
		return (1);
	if (ft_export_one(&data->env, &data->export, old_pwd) != 0)
		return (free(old_pwd), free(new_pwd), 1);
	if (ft_export_one(&data->env, &data->export, new_pwd) != 0)
		return (free(old_pwd), free(new_pwd), 1);
	return (free(old_pwd), free(new_pwd), 0);
}
