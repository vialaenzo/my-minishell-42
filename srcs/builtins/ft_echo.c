#include "minishell.h"

static void	ft_skip_newline(char **args, int *index, bool *newline)
{
	int	j;

	while (args[*index] && args[*index][0] == '-')
	{
		j = 1;
		while (args[*index][j] == 'n')
			j++;
		if (args[*index][j - 1] == 'n' && args[*index][j] == '\0')
		{
			*newline = false;
			(*index)++;
		}
		else
			break ;
	}
}

int	ft_echo(char **args)
{
	int		i;
	bool	newline;

	args++;
	newline = true;
	i = 0;
	ft_skip_newline(args, &i, &newline);
	while (args[i])
	{
		ft_printf(1, "%s", args[i]);
		if (args[i + 1])
			ft_printf(1, " ");
		i++;
	}
	if (newline)
		ft_printf(1, "\n");
	return (0);
}
