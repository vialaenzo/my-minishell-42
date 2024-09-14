#include "minishell.h"

size_t	ft_cmd_size(t_cmd **cmd)
{
	t_cmd *(current) = *cmd;
	if (!current)
		return (0);
	while (current->prev)
		current = current->prev;
	size_t (size) = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
