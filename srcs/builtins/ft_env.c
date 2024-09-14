#include "minishell.h"

int	ft_env(t_liste **env)
{
	t_liste	*current;

	ft_env_sort(env);
	current = *env;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		ft_printf(1, "%s\n", current->str);
		current = current->next;
	}
	return (0);
}
