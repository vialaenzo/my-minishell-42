#include "minishell.h"

int	ft_unset_one(t_liste **env, char *var)
{
	t_liste	*next;
	t_liste	*prev;

	if (!var)
		return (0);
	t_liste *(curr) = *env;
	while (curr)
	{
		if (ft_strncmp(var, curr->str, ft_strlen(var)) == 0
			&& (curr->str[ft_strlen(var)] == '='
				|| curr->str[ft_strlen(var)] == '\0'))
		{
			prev = curr->prev;
			next = curr->next;
			if (prev)
				prev->next = next;
			else
				*env = next;
			if (next)
				next->prev = prev;
			return (free(curr->str), free(curr), 1);
		}
		curr = curr->next;
	}
	return (1);
}

int	ft_unset(t_data *data, char **args)
{
	int (ret) = 0;
	if (ft_size_tab(args) == 1)
		return (ft_printf(2, "minishell: %s : not \
			enough arguments\n", args[0]), 1);
	args++;
	while (*args)
	{
		if (!ft_check_key(*args))
		{
			ft_printf(2, "minishell: export: '%s': not a valid identifier\n",
				*args);
			args++;
			continue ;
		}
		ret = ft_unset_one(&data->env, *args);
		if (ret == 0)
			return (-2);
		ret = ft_unset_one(&data->export, *args);
		if (ret == 0)
			return (-2);
		args++;
	}
	return (0);
}
