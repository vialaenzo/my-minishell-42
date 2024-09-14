#include "minishell.h"

int	ft_pwd(char **args)
{
	int	i;

	if (!args || !args[0])
		return (1);
	if (ft_size_tab(args) > 1 && args[1][0] == '-')
	{
		i = 0;
		while (args[1][i] == '-')
			i++;
		if (args[1][i] != '\0')
		{
			ft_printf(1, "minishell: pwd: %c%c: invalid option\n", args[1][0],
				args[1][1]);
			return (2);
		}
	}
	char *(path) = getcwd(NULL, 0);
	if (!path)
		return (perror("minishell: getcwd"), 1);
	ft_printf(1, "%s\n", path);
	free(path);
	return (0);
}
