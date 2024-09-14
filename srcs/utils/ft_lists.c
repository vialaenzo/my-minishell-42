#include "minishell.h"

t_liste	*ft_liste_new(char *str)
{
	if (!str)
		return (NULL);
	t_liste *(liste) = malloc(sizeof(t_liste));
	if (!liste)
		return (NULL);
	liste->str = str;
	liste->next = NULL;
	liste->prev = NULL;
	return (liste);
}

int	ft_liste_add_back(t_liste **list, t_liste *liste)
{
	if (!liste)
		return (0);
	if (!*list)
	{
		*list = liste;
		return (1);
	}
	t_liste *(current) = *list;
	while (current->next)
		current = current->next;
	current->next = liste;
	liste->prev = current;
	return (1);
}

size_t	ft_liste_size(t_liste **list)
{
	t_liste *(current) = *list;
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

void	ft_liste_clear(t_liste **list)
{
	t_liste	*next;

	if (!list || !*list)
		return ;
	t_liste *(current) = *list;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*list = NULL;
}
