#include "minishell.h"

static int	ft_get_key_value(char **key, char **value, char *str)
{
	if (!key || !value || !str)
		return (0);
	char *(equal) = ft_strchr(str, '=');
	if (str[0] == '=')
		return (ft_printf(2, "minishell: %s: not a valid identifier\n", str),
			0);
	if (!equal)
	{
		*key = ft_strdup(str);
		if (!*key)
			return (0);
		*value = ft_strdup("");
		if (!*value)
			return (free(*key), *key = NULL, 0);
		return (1);
	}
	*key = ft_substr(str, 0, equal - str);
	if (!*key)
		return (0);
	if (ft_strlen(*key) == 0)
		return (free(*key), *key = NULL, 0);
	*value = ft_substr(str, equal - str + 1, ft_strlen(str) - (equal - str));
	if (!*value)
		return (free(*key), *key = NULL, 0);
	return (1);
}

int	ft_check_key(char *key)
{
	int	i;

	if (ft_isdigit(key[0]) || ft_strlen(key) == 0)
		return (0);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	fill_export_str(char *key, char *value, char **export_str)
{
	free(*export_str);
	*export_str = NULL;
	if (!key || !value)
		return (0);
	if (*value == '\0')
	{
		*export_str = ft_strjoin(key, "=\"\"");
		if (!*export_str)
			return (0);
		return (1);
	}
	*export_str = ft_strjoin(key, "=\"");
	*export_str = ft_strjoin_free(*export_str, value);
	*export_str = ft_strjoin_free(*export_str, "\"");
	if (!*export_str)
		return (0);
	return (1);
}

int	ft_export_one(t_liste **env, t_liste **export, char *str)
{
	char *(key) = NULL;
	char *(value) = NULL;
	if (!str || !ft_get_key_value(&key, &value, str))
		return (1);
	if (!ft_check_key(key))
		return (ft_printf(2,
				"minishell: export: '%s': not a valid identifier\n", str),
			free(key), free(value), 0);
	char *(export_str) = ft_strdup(str);
	if (!export_str)
		return (free(key), free(value), 1);
	ft_unset_one(env, key);
	ft_unset_one(export, key);
	if (ft_strchr(str, '='))
	{
		if (!ft_liste_add_back(env, ft_liste_new(ft_strdup(str))))
			return (free(key), free(value), free(export_str), 1);
		if (!fill_export_str(key, value, &export_str))
			return (free(key), free(value), 1);
	}
	if (!ft_liste_add_back(export, ft_liste_new(export_str)))
		return (free(key), free(value), free(export_str), 1);
	return (free(key), free(value), 0);
}

int	ft_export(t_data *data, char **args)
{
	int	ret;

	if (!args)
		return (1);
	if (ft_size_tab(args) == 1)
		return (ft_env(&data->export), 0);
	if (1 && ft_size_tab(args) > 1 && args[1][0] == '-')
	{
		ft_printf(1, "minishell: export: %c%c: invalid option\n", args[1][0],
			args[1][1]);
		return (2);
	}
	args++;
	while (*args)
	{
		if (ft_strnstr(*args, "+=", ft_strlen(*args)))
			ret = ft_export_one_append(&data->env, &data->export, *args);
		else
			ret = ft_export_one(&data->env, &data->export, *args);
		if (ret != 0)
			return (ret);
		args++;
	}
	return (0);
}
