#include "minishell.h"

static int	ft_get_key_value(char **key, char **value, char *str)
{
	if (!key || !value || !str)
		return (0);
	char *(plusegal) = ft_strnstr(str, "+=", ft_strlen(str));
	*key = ft_substr(str, 0, plusegal - str);
	if (!*key)
		return (0);
	if (ft_strlen(*key) == 0)
		return (free(*key), *key = NULL, 0);
	*value = ft_substr(str, (plusegal + 1) - str + 1, ft_strlen(str)
			- ((plusegal + 1) - str));
	if (!*value)
		return (free(*key), *key = NULL, 0);
	return (1);
}

char	*construct_value(char *key, char *ap_value, int quote)
{
	char *(add_str) = ft_strjoin(key, "=");
	if (!add_str)
		return (NULL);
	if (quote == 1)
	{
		add_str = ft_strjoin_free(add_str, "\"");
		add_str = ft_strjoin_free(add_str, ap_value);
		add_str = ft_strjoin_free(add_str, "\"");
	}
	else
		add_str = ft_strjoin_free(add_str, ap_value);
	return (add_str);
}

int	ft_change_value(t_liste **(liste), char *ap_value, char *key, int quote)
{
	t_liste *(tmp) = *liste;
	char *(tmp_str) = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, key, ft_strlen(key)))
		{
			if (quote == 1)
				*ft_strrchr(tmp->str, '\"') = '\0';
			tmp_str = ft_strjoin(tmp->str, ap_value);
			if (quote == 1)
				tmp_str = ft_strjoin_free(tmp_str, "\"");
			if (!tmp_str)
				return (0);
			free(tmp->str);
			tmp->str = tmp_str;
			return (1);
		}
		tmp = tmp->next;
	}
	char *(add_str) = construct_value(key, ap_value, quote);
	if (!ft_liste_add_back(liste, ft_liste_new(add_str)))
		return (free(add_str), 0);
	return (1);
}

int	ft_export_one_append(t_liste **env, t_liste **export, char *str)
{
	(void)export;
	char *(key) = NULL;
	char *(ap_value) = NULL;
	if (!str || !ft_get_key_value(&key, &ap_value, str))
		return (1);
	ft_printf(2, "key : %s | value : %s\n", key, ap_value);
	if (!ft_check_key(key))
		return (ft_printf(2,
				"minishell: export: '%s': not a valid identifier\n", str),
			free(key), free(ap_value), 0);
	if (!ft_change_value(env, ap_value, key, 0))
		return (free(ap_value), free(key), 1);
	if (!ft_change_value(export, ap_value, key, 1))
		return (free(ap_value), free(key), 1);
	return (free(key), free(ap_value), 0);
}
