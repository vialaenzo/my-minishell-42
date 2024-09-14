#include "minishell.h"

t_cmd	*ft_cmd_new(int infile, int outfile, char **cmd_param)
{
	t_cmd *(new) = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->skip_cmd = false;
	new->infile = infile;
	new->outfile = outfile;
	new->cmd_param = cmd_param;
	new->path = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_cmd_add_back(t_cmd **list, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!*list)
	{
		*list = cmd;
		return (1);
	}
	t_cmd *(current) = *list;
	while (current->next)
		current = current->next;
	current->next = cmd;
	cmd->prev = current;
	return (1);
}

t_cmd	*ft_cmd_last(t_cmd **list)
{
	t_cmd *(current) = *list;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

void	free_all_cmd(t_cmd *tmp)
{
	if (tmp->infile > 0)
		close(tmp->infile);
	tmp->infile = -2;
	if (tmp->outfile > 0)
		close(tmp->outfile);
	tmp->outfile = -2;
	if (tmp->path)
	{
		free(tmp->path);
		tmp->path = NULL;
	}
	ft_free_tab(tmp->cmd_param);
}

void	ft_cmd_clear(t_cmd **list)
{
	t_cmd *(current) = *list;
	t_cmd *(tmp) = NULL;
	if (!list || !*list)
		return ;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		tmp = current->next;
		free_all_cmd(current);
		free(current);
		current = tmp;
	}
	*list = NULL;
}
