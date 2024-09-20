/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:24 by eviala            #+#    #+#             */
/*   Updated: 2024/09/20 12:29:08 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	error_token(t_token *token)
{
	if (!token->next)
		ft_error("syntax error near unexpected token 'newline'");
	else
		ft_printf(2, "minishell: syntax error near unexpected token '%s'\n",
			token->next->str);
	return (false);
}

int	ft_str_add_chr(char **str, char c)
{
	if (!str || !(*str))
		return (-1);
	char *(str_new) = malloc((ft_strlen(*str) + 2) * sizeof(char));
	if (!str_new)
		return (-1);
	int(i) = -1;
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
	int(size) = 0;
	if (!tab)
		return (-1);
	while (tab && *tab)
	{
		size++;
		tab++;
	}
	return (size);
}

bool	verif_special(t_data *data)
{
	t_token(*tmp) = data->token;
	while (tmp->prev)
		tmp = tmp->prev;
	if (!tmp || !tmp->str)
		return (data->exit_code = 1, false);
	if (tmp->str[0] == '\0')
		return (data->exit_code = 0, false);
	if (!ft_strncmp(tmp->str, ":", 2) || !ft_strncmp(tmp->str, "#", 2))
		return (data->exit_code = 0, false);
	else if (!ft_strncmp(tmp->str, "!", 2))
		return (data->exit_code = 1, false);
	return (true);
}
