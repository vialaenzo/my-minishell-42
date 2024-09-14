#include "minishell.h"

static int	ft_arg_to_int(char *arg, int *ret)
{
	unsigned long (value) = 0;
	int (i) = 0;
	int (sign) = 1;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= arg[i] && arg[i] <= '9')
	{
		if (value > (ULONG_MAX - (arg[i] - '0')) / 10)
			return (1);
		value = value * 10 + (arg[i] - '0');
		i++;
	}
	if (arg[i] != '\0')
		return (1);
	*ret = (int)((value * sign) % 256);
	return (0);
}

void	ft_exit(t_data *data, char **args)
{
	int (num) = 0;
	int (error) = 0;
	if (!args || !(args[0]))
		return ;
	if (args[1])
	{
		error = ft_arg_to_int(args[1], &num);
		if (error)
		{
			ft_printf(2, "minishell: %s : numeric argument required\n",
				args[1]);
			data->exit_code = 1;
			return ;
		}
		if (args[2])
		{
			ft_error("minishell: exit: too many arguments");
			data->exit_code = 1;
			return ;
		}
		data->exit_code = num;
	}
	free_everything(data, NULL, data->exit_code);
}
