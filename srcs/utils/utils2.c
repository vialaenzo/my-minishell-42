#include "minishell.h"

bool	error_token(t_token *token)
{
	if (token->next == NULL)
		ft_error("syntax error near unexpected token 'newline'");
	else
		ft_printf(2, "minishell: syntax error near unexpected token '%s'\n"\
		, token->next->str);
	return (false);
}

int	ft_str_add_chr(char **str, char c)
{
	if (!str || !(*str))
		return (-1);
	char *(str_new) = malloc((ft_strlen(*str) + 2) * sizeof(char));
	if (!str_new)
		return (-1);
	int (i) = -1;
	while ((*str)[++i])
		str_new[i] = (*str)[i];
	str_new[i++] = c;
	str_new[i] = '\0';
	free(*str);
	*str = str_new;
	return (1);
}

int	ft_size_tab(char **tab)
{
	int (size) = 0;
	if (!tab)
		return (-1);
	while (tab && *tab)
	{
		size++;
		tab++;
	}
	return (size);
}
