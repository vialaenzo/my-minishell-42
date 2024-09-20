/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:18 by eviala            #+#    #+#             */
/*   Updated: 2024/09/20 10:27:50 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_has(char *key, t_liste *env)
{
	if (!key || !env)
		return (0);
	t_liste *(current) = env;
	while (current)
	{
		if (ft_strncmp(key, current->str, ft_strlen(key)) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_env_get(char *key, char **value, t_liste *env)
{
	if (!key || !env)
		return (0);
	t_liste *(current) = env;
	while (current)
	{
		if (ft_strncmp(key, current->str, ft_strlen(key)) == 0
			&& current->str[ft_strlen(key)] == '=')
		{
			*value = ft_strdup(current->str + ft_strlen(key) + 1);
			if (!(*value))
				return (0);
			return (1);
		}
		current = current->next;
	}
	*value = ft_strdup("");
	if (!(*value))
		return (0);
	return (0);
}

int	ft_env_sort(t_liste **env)
{
	char	*temp;
	t_liste	*current;

	size_t(size) = ft_liste_size(env);
	while (size--)
	{
		current = *env;
		while (current && current->next)
		{
			if (ft_strcmp(current->str, current->next->str) > 0)
			{
				temp = current->str;
				current->str = current->next->str;
				current->next->str = temp;
			}
			current = current->next;
		}
	}
	return (size);
}

int	ft_env_to_tab(t_liste **env, char ***tab)
{
	size_t(size) = (int)ft_liste_size(env);
	*tab = malloc((size + 1) * sizeof(char *));
	if (!(*tab))
		return (0);
	int (i) = 0;
	t_liste *(current) = *env;
	while (current)
	{
		(*tab)[i] = ft_strdup(current->str);
		if (!(*tab)[i])
		{
			while (--i >= 0)
				free((*tab)[i]);
			free(*tab);
			return (0);
		}
		current = current->next;
		i++;
	}
	return ((*tab)[i] = NULL, 1);
}

int	ft_env_new(t_data *data)
{
	if (!data || data->env)
		return (0);
	char *(pwd) = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	char *(pwd_entry) = ft_strjoin("PWD=", pwd);
	if (!pwd_entry)
		return (0);
	ft_export_one(&data->env, &data->export, pwd_entry);
	ft_export_one(&data->env, &data->export, "SHLVL=1");
	ft_liste_add_back(&data->env, ft_liste_new(ft_strdup("_=/usr/bin/env")));
	ft_export_one(&data->env, &data->export, "OLDPWD");
	free(pwd);
	free(pwd_entry);
	if (ft_liste_size(&data->export) != 3 || ft_liste_size(&data->export) != 3)
		return (0);
	return (1);
}
