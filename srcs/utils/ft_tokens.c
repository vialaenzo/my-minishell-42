#include "minishell.h"

t_token	*ft_token_new(char *str, t_type type)
{
	if (!str)
		return (NULL);
	t_token *(token) = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

int	ft_token_add_back(t_token **list, t_token *token)
{
	t_token	*current;

	if (!token)
		return (0);
	if (!*list)
	{
		*list = token;
		return (1);
	}
	current = ft_token_last(list);
	current->next = token;
	token->prev = current;
	return (1);
}

size_t	ft_token_size(t_token **list)
{
	t_token *(current) = *list;
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

void	ft_token_clear(t_token **list)
{
	t_token	*next;

	if (!list || !*list)
		return ;
	t_token *(current) = *list;
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

t_token	*ft_token_last(t_token **list)
{
	t_token *(current) = *list;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}
