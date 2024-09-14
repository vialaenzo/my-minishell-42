#include "minishell.h"

static int	ft_expand_code(char **str, int *index, t_data *data)
{
	char *(str_num) = ft_itoa(data->exit_code);
	if (!str_num)
		return (-1);
	int (i) = -1;
	while (str_num[++i])
	{
		if (!ft_str_add_chr(str, str_num[i]))
			return (free(str_num), -1);
	}
	(*index)++;
	free(str_num);
	return (1);
}

static int	ft_expand_var(char **value, char *str, int *index, t_data *data)
{
	char *(str_var) = NULL;
	char *(key) = ft_strdup("");
	if (!key)
		return (-1);
	int (i) = 1;
	while (ft_isalnum(str[*index + i]) || str[*index + (i)] == '_')
	{
		if (!ft_str_add_chr(&key, str[*index + i]))
			return (free(key), -1);
		i++;
	}
	ft_env_get(key, &str_var, data->env);
	if (!str_var)
		return (free(key), -1);
	i = -1;
	while (str_var[++i])
	{
		if (!ft_str_add_chr(value, str_var[i]))
			return (free(key), free(str_var), -1);
	}
	return (*index += ft_strlen(key), free(str_var), free(key), 1);
}

static int	ft_get_quotation(int *quote, char c)
{
	if ((*quote) == 0 && c == '\'')
		(*quote) = 1;
	else if ((*quote) == 0 && c == '"')
		(*quote) = 2;
	else if ((*quote) == 1 && c == '\'')
		(*quote) = 0;	
	else if ((*quote) == 2 && c == '"')
		(*quote) = 0;
	return (*quote);
}

int	ft_expand(char **line, t_data *data)
{
	int (i) = -1;
	int (quote) = 0;
	int (res) = 1;
	char *(str) = ft_strdup("");
	if (!str)
		return (0);
	while ((*line)[++i])
	{
		if (ft_get_quotation(&quote, (*line)[i]) == 1)
			res = ft_str_add_chr(&str, (*line)[i]);
		else if ((*line)[i] == '$' && (*line)[i + 1] == '?')
			res = ft_expand_code(&str, &i, data);
		else if ((*line)[i] == '$' && (ft_isalpha((*line)[i + 1])))
			res = ft_expand_var(&str, *line, &i, data);
		else if ((*line)[i] == '$' && (*line)[i + 1] == '_')
			res = ft_expand_var(&str, *line, &i, data);
		else
			res = ft_str_add_chr(&str, (*line)[i]);
		if (res == -1)
			return (free(str), 0);
	}
	return (free(*line), *line = str, 1);
}
